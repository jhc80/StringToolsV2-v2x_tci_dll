require("common")

--除掉字符串中的 '-' 等不能在变量中出现的字符--
function convert_invalid_chars(str)
    local tmp = string.gsub(str,"-","_");
    return tmp;
end

function to_upper_underline_case(str)
    return string.upper(convert_invalid_chars(
        camel_to_underline_case(str)
    ));
end

function to_lower_underline_case(str)
    return string.lower(convert_invalid_chars(
        camel_to_underline_case(str)
    ));
end

--生成enum类型的成员名字--
function enum_value_name(enum_type, name)
    return convert_invalid_chars(enum_type.."_"..name);
end

--生成bit string类型的成员名字--
function bit_string_value_name(type_name, name)
    return convert_invalid_chars(type_name.."_"..name);
end

function get_enum_init_value(enum_name)
    local ref_type = asn1_helper:FindReferenceTypeByName(enum_name);
    if ref_type and ref_type.members then    
        return enum_member_name(ref_type.members[1].Identifier,ref_type);
    end    
end

--转换成员类型的名字--
function class_member_type_name(member)

    local asn1_hits = string.format("[Asn1Type=%s",
        expr_type_to_string(member.ref_type.expr_type)
    );
    
    if member.is_container then    
        local ref_type = asn1_helper:FindReferenceTypeByName(member.ref_type.name);
        if ref_type then
            asn1_hits = asn1_hits .." "..ref_type.entry_ref_type.name;
        end            
    end
    
    asn1_hits = asn1_hits.."]";
    
    if member.ref_type.expr_type == ASN_BASIC_ENUMERATED then
        return {
            type_name = enum_name(member.ref_type.name),
            init_value = get_enum_init_value(member.ref_type.name),
            hint = asn1_hits,
        }
    end

    if member.ref_type.expr_type == ASN_BASIC_BIT_STRING then
        return {
            type_name = bit_string_name(member.ref_type.name),
            hint = asn1_hits,
        }
    end

    if member.ref_type.is_raw then
        if member.ref_type.c_type then
            return {            
                type_name = member.ref_type.c_type,
                hint = asn1_hits,
            }
        end
    end

    if member.is_basic_type then
        return {
            type_name = basic_type_name(member.ref_type.name),
            hint = asn1_hits,
        }
    end

    return {
        type_name = class_name(member.ref_type.name),
        hint = asn1_hits,
    }
end 

--enum 类型的代码生成
function code_enum(member)   
    printfnl("enum %s{",enum_name(member.Identifier));
    for_each_member(member,function(m)            
        printfnl("    %s = %s,",
            enum_member_name(m.Identifier,member),
            m.value.value.v_integer
        );
    end);
    printfnl("};");
end

--bit_string 类型的代码生成
function code_bit_string(member)   
    if switch.bit_string_typedef then
        printfnl("typedef %s %s;",
            c_class_name(member.ref_type.c_type),
            c_class_name(member.Identifier)
        );    
        printnl("");
    end
    
    if switch.bit_string then
        printfnl("enum %s{",bit_string_enum_name(member.Identifier));
        for_each_member(member,function(m)            
            printfnl("    %s = %d,",
                bit_string_member_name(m.Identifier,member),
                m.value.value.v_integer
            );
        end);        
        printfnl("};");
    end
end

--choice 类型的代码生成
function code_choice(member)
    
    local def_present = choice_enum_member_name("NOTHING",member);
    
    if switch.choice_enum then    
        printfnl("enum %s{",choice_enum_name(member.Identifier));           
        printfnl("    %s,",def_present);
        for_each_member(member,function(m)
            printfnl("    %s,",
                choice_enum_member_name(m.Identifier,member)
            );
        end);        
        printfnl("};");
        printnl("");
    end

    if switch.choice then
        printfnl("[Asn1Choice]");
        printfnl("class %s{",class_name(member.Identifier));
        printfnl("    %s present = %s;",choice_enum_name(member.Identifier),def_present);
        
        for_each_member(member,function(m)
          
            print("    [optional]");
            
            local mtype = class_member_type_name(m);
            
            if mtype.hint then
                printf("%s",mtype.hint);
            end
            
            printfnl(" %s %s;",
                mtype.type_name,
                class_member_name(m.Identifier)
            );
        end);
        printfnl("}");
    end
end

--sequence 类型的代码生成
function code_sequence(member,level)   
    printfnl("class %s{",class_name(member.Identifier));
    for_each_member(member,function(m)
        print("    ");
       
        local has_hint = false;    
        if m.is_optional then
            has_hint = true;
            print("[optional]");
        end
                        
        local mtype = class_member_type_name(m);
        if mtype.hint then
            has_hint = true;
            printf("%s",mtype.hint);
        end
        
        if has_hint then
            print(" ");
        end
        
        printfnl("%s %s%s;",
            mtype.type_name,
            class_member_name(m.Identifier),
            mtype.init_value and " = "..mtype.init_value or ""
        );        
    end);
    printfnl("}");
end


--basic 类型的代码生成
function code_basic_type(member)
    printfnl("typedef %s %s;",
        member.ref_type.c_type,
        basic_type_name(member.Identifier)
    );    
end

function code_container_h_file(member)
    local  source=string.format([[
        #ifndef __T_ASN1P_%s_H
        #define __T_ASN1P_%s_H

        #include "commonarray.h"
        #include "%s.h"
        #include "%s.h"
        #include "asn1p_common_h.h"

        namespace %s {

        typedef CCommonArray<%s> %sBase;

        class %s:public %sBase{
        public:
            status_t Copy(%s *_p);
            status_t Push(%s*_p); 
            status_t LoadRawAsn1(%s_t *list);
            status_t SaveRawAsn1(%s_t *list);
        };

        }  //namespace %s

        #endif
    ]],
        to_upper_underline_case(member.Identifier),
        to_upper_underline_case(member.Identifier),
        to_file_name(member.entry_ref_type.name),
        member.Identifier,
        name_space,
        c_class_name(member.entry_ref_type.name),c_class_name(member.Identifier),
        c_class_name(member.Identifier),c_class_name(member.Identifier),
        c_class_name(member.Identifier), --copy
        c_class_name(member.entry_ref_type.name), --push
        member.Identifier,
        member.Identifier,
        name_space
    );

    local h_file_name = FileManager.ToAbsPath(
        save_path.."/"..to_file_name(member.Identifier)..".h"
    );
    
    local file = new_file(h_file_name,"wb+");
    if not file then
        printfnl("create file %s fail.",h_file_name);
        return
    end
     
    file:Puts(long_text(source,8));
    file:Destroy();
    
    printfnl("save file to %s",h_file_name);
    
end

function code_container_cpp_file(member)

local source=string.format([[
        #include "%s.h"
        #include "asn1p_common_cpp.h"

        namespace %s {
       
        status_t %s::Copy(%s *_p)
        {
            int i;
            ASSERT(_p);
            %sBase::Destroy();
            %sBase::Init(_p->GetLen());
            for(i = 0; i < _p->GetLen(); i++)
            {
                %s *p = _p->GetElem(i);
                ASSERT(p);
                %s *tmp;
                NEW(tmp,%s);
                tmp->Init();
                tmp->Copy(p);
                if(!this->PushPtr(tmp))
                {
                    DEL(tmp);
                }
            }
            return OK;
        }

        status_t %s::Push(%s *_p)
        {
            ASSERT(_p);
            
            %s *tmp;
            NEW(tmp,%s);
            tmp->Init();
            tmp->Copy(_p);
            if(!this->PushPtr(tmp))
            {
                DEL(tmp);
                return ERROR;
            }           
            return OK;
        }
        
        status_t %s::LoadRawAsn1(%s_t *list)
        {
            ASSERT(list);
            this->Clear();
            int count = list->list.count;
            %s_t **elems = list->list.array;
            ASSERT(elems);
            for(int i = 0; i < count; i++)
            {
                %s *tmp;
                NEW(tmp,%s);
                tmp->Init();
                tmp->LoadRawAsn1(elems[i]);
                if(!this->PushPtr(tmp))
                {
                    DEL(tmp);
                    return ERROR;
                }
          }
            return OK;
        }
        
        status_t %s::SaveRawAsn1(%s_t *list)
        {
            ASSERT(list);
            SEQUENCE_OF_free(&asn_DEF_%s,list,ASFM_FREE_UNDERLYING_AND_RESET);
            for(int i = 0; i < this->GetLen(); i++)
            {
                %s *elem = this->GetElem(i);
                ASSERT(elem);
                %s_t *node = ASN1_ALLOC(%s_t,1);
                elem->SaveRawAsn1(node);
                ASN_SEQUENCE_ADD(&list->list, node);
            }
            return OK;
        }
        }  //name space %s
    ]],
        to_file_name(member.Identifier),
        name_space,
        c_class_name(member.Identifier),
        c_class_name(member.Identifier),
        --Copy
        c_class_name(member.Identifier),c_class_name(member.Identifier),
        c_class_name(member.Identifier),
        c_class_name(member.Identifier),
        c_class_name(member.entry_ref_type.name),
        c_class_name(member.entry_ref_type.name),
        c_class_name(member.entry_ref_type.name),
        --Push
        c_class_name(member.Identifier),c_class_name(member.entry_ref_type.name),
        c_class_name(member.entry_ref_type.name),
        c_class_name(member.entry_ref_type.name),        
        --LoadRawAsn1
        c_class_name(member.Identifier),member.Identifier,
        member.entry_ref_type.name,
        c_class_name(member.entry_ref_type.name),
        c_class_name(member.entry_ref_type.name),
        --SaveRawAsn1
        c_class_name(member.Identifier),member.Identifier,
        member.Identifier,
        c_class_name(member.entry_ref_type.name),
        member.entry_ref_type.name,member.entry_ref_type.name,
        name_space
    );
    
    local cpp_file_name = FileManager.ToAbsPath(
        save_path.."/"..to_file_name(member.Identifier)..".cpp"
    );
    
    local file = new_file(cpp_file_name,"wb+");
    if not file then
        printfnl("create file %s fail.",cpp_file_name);
        return
    end
     
    file:Puts(long_text(source,8));
    file:Destroy();
    
    printfnl("save file to %s",cpp_file_name);
end

--container 类型的代码生成
function code_container(member)    
    if switch.container then
        if member.ref_type.expr_type == ASN_CONSTR_SEQUENCE_OF then
            local is_basic = (member.entry_ref_type.expr_type & ASN_BASIC_MASK) == ASN_BASIC_MASK;
            printfnl("[Stack of %s%s]",
                member.entry_ref_type.name,
                is_basic and ",basic" or ""
            );
        end   
        printfnl("class %s{",class_name(member.Identifier));
        printnl("}");
    end
   
    if switch.container_files and save_path ~="" then       
        code_container_h_file(member);
        code_container_cpp_file(member);
    end
   
end

--其他类型的String--
function code_other_string(member)   
    printfnl("typedef %s %s;",
        c_class_name(member.ref_type.c_type),
        basic_type_name(member.Identifier)
    );  
end

function code_idl(member,level)    
    if member.meta_type ~= AMT_TYPE then   
        return
    end
    if  member.expr_type == ASN_BASIC_ENUMERATED then
        if switch.enum then
            printnl("/// enum");
            code_enum(member);
            printnl("");
        end
    elseif member.expr_type == ASN_BASIC_BIT_STRING then    
        if switch.bit_string or switch.bit_string_typedef then
            printnl("/// bit string");
            code_bit_string(member);
            printnl("");
        end
    elseif member.expr_type == ASN_CONSTR_CHOICE then
        if switch.choice or switch.choice_enum then
            printnl("/// choice");
            code_choice(member);
            printnl("");
        end
    elseif member.expr_type == ASN_CONSTR_SEQUENCE then
        if switch.sequence then
            printnl("/// sequence");
            code_sequence(member,level);
            printnl("");
        end
    elseif member.is_string then
        if switch.string_typedef then
            printnl("/// string");
            code_other_string(member);
            printnl("");
        end
    elseif member.is_basic_type then
        if switch.basic_type then
            printnl("/// basic");
            code_basic_type(member);
            printnl("");
        end
    elseif member.is_container then
        if switch.container or switch.container_files then
            printnl("/// container");
            code_container(member);
            printnl("");
        end
    else
        for_each_member(member,function(m)            
            code_idl(m,level+1);   
        end);   
    end
end
