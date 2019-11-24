function print_all_keys(obj)
    for k,v in pairs(obj) do
        printnl(k);
    end
    printnl("------------------");
end

-----------------------------------------------
function dump_members_name(obj,level)
    if not level then
        level = 0;
    end
    
    if not obj.members then
        return false;
    end            
   
    for k,v in ipairs(obj.members) do    
        for i=1, level, 1 do
            print("    ");
        end
        printnl(v.Identifier);        
        if v.members then
            dump_members_name(v,level+1);
        end        
    end 
end
-----------------------------------------------
function for_each_module(tab,callback)
    for _,m in ipairs(tab) do
        if callback(m) then
            return true;
        end
    end
end
-----------------------------------------------
--可以覆盖此方法，实现对名字冲突的修正，比如 long 这个
--名字就和c语言的关键字有冲突
function fix_asn1_member_name(m)
end
-----------------------------------------------
function for_each_member(obj,callback,all)
    if not obj.members then
        return;
    end    
    
    for _,m in ipairs(obj.members) do		
        fix_asn1_member_name(m);        
		local expr_type = m.ref_type.expr_type;
        m.parent = obj;
	    m.is_basic_type = (expr_type & ASN_BASIC_MASK) == ASN_BASIC_MASK;
        m.is_string = (expr_type & ASN_STRING_MASK) ~= 0;        
        m.is_object = not m.is_basic_type;
        m.is_container = expr_type == ASN_CONSTR_SET_OF or expr_type == ASN_CONSTR_SEQUENCE_OF;        
        m.is_optional = (m.marker.flags == 7);
        m.is_choice = expr_type == ASN_CONSTR_CHOICE;
        
        if expr_type == ASN_BASIC_BIT_STRING then
            m.is_basic_type = false;
            m.is_bit_string = true;
        end
        
        if expr_type == ASN_BASIC_OCTET_STRING then
            m.is_basic_type = false;
            m.is_string = true;
        end
        
        if expr_type == ASN_BASIC_ENUMERATED then
            m.is_enum = true;
            m.is_basic_type = true;
        end
        
        if all then
            if not m.Identifier then
                m.Identifier = "";
            end
        end
        
        if m.Identifier and m.Identifier ~= "..." then
            if callback(m) then
                return true;
            end
        end
    end    
end

--生成嵌套结构的类型名字--
function make_inner_complex_type_name(m)
    if not m.Identifier then  return  end
    if m.Identifier == "" then return "" end
    
    local p = m.parent; 
    
    local name = m.Identifier;
    while p do
        if p.Identifier then
                name = p.Identifier.."__"..name;
        end  
        p = p.parent;
    end
    return name;
end

function extract_inner_members(member,all,level)
    if level >= 1 then
        if member.expr_type == ASN_CONSTR_SEQUENCE 
            or member.expr_type == ASN_CONSTR_CHOICE
        then        
            --生成一个新的obj
            local new_obj={
                Identifier = make_inner_complex_type_name(member),
                meta_type = AMT_TYPE,
                expr_type = member.expr_type,
                members = member.members,  --原有的member不要忘了
                ref_type = {
                    expr_type = member.ref_type.expr_type,
                },
            }                                 
            --原有的类型名字要替换成新的类型
            member.ref_type.name = new_obj.Identifier
            table.insert(all,new_obj);
        end
        
        if member.expr_type == ASN_CONSTR_SEQUENCE_OF
            or member.expr_type == ASN_CONSTR_SET_OF
        then           
            --分两种情况，一种是匿名结构体
            --另一种是命名结构体，处理起来是不一样的                
            local anonymous = false;
            local entry_type_name;
            local entry_expr_type;
            
            if member.members[1].members then
                anonymous = true;
            end

            if anonymous then              
                local m = member.members[1];
                m.Identifier = make_inner_complex_type_name(member).."_Member"; 
                table.insert(all,m);                
                member.ref_type.name = make_inner_complex_type_name(member).."_List"; 
                --断开members,防止重复添加
                member.members = nil;                
                entry_type_name = m.Identifier;
                entry_expr_type = m.expr_type;
            else
                entry_type_name = member.entry_ref_type.name;
                entry_expr_type = member.entry_ref_type.expr_type;
            end
            
            --再生成一个member类型的list类型            
            local list_type_name;
            if anonymous then
                list_type_name = make_inner_complex_type_name(member).."_List";
            else
                list_type_name = entry_type_name.."_List";
                member.ref_type.name = list_type_name;
            end
            
            local list_obj = {
                Identifier = list_type_name,
                is_container = true,
                meta_type = AMT_TYPE,

                ref_type = {
                    expr_type = member.expr_type,
                },
    
                entry_ref_type={
                    name = entry_type_name,
                    expr_type = entry_expr_type,
                },
            }

            table.insert(all,list_obj);
        end        
    end
    
    for_each_member(member,function(m)        
        extract_inner_members(m,all,level+1);    
    end,true);    
    
end

--展开所有的内置的复杂结构类型，如果有正常的处理流程--
--一定要先运行这个函数，因此此函数会为内部的结构体重新命名--
function extract_all_inner_members(asn1_table)
    local all = {};
    for_each_module(asn1_table,function(module)
        for_each_member(module,function(m)
            if m.meta_type == AMT_TYPE then                               
                extract_inner_members(m,all,0);
            end
        end);           
    end);
    return all;
end

--把减号替换成下划线，使名字中不能包含非法字符--
function asn_valid_name(str)
    return string.gsub(str,"-","_");
end





