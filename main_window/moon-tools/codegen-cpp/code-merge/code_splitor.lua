require("common")

CodeSplitor = class();

function CodeSplitor:ctor()
    self.m_code_type = "cpp";
end

function CodeSplitor:SplitSourceFile(file)
    local file_ref = nil;
    
    if type(file) == "string" then    
        local ext = FileManager.SliceFileName(file,FN_EXT);
        self.m_code_type = ext;
    
        file_ref = new_file(file,"rb");
        if not file_ref then return end
        file = file_ref:FileBase();
    end
   
    local lex_xx = nil;
    local lex = nil;
    
    if self.m_code_type == "lua" then
        lex_xx = LexerLua.new();
        lex = lex_xx:Lexer();
    else
        lex_xx = LexerCpp.new();
        lex = lex_xx:Lexer();
    end

    lex:LoadFile(file);
    
    local start_block_name;
    local start_extra_name;
    local tab = {};
    
    local mf,mf_file = new_memfile();
    local tmp, tmp_file = new_memfile();
    
    while not lex:IsEnd() do
        mf_file:SetSize(0);
        local type = lex_xx:NextToken(mf_file);        
        local cur_token = mf_file;
        
        if type == TOKEN_MULTI_LINE_COMMENTS or type == TOKEN_SINGLE_LINE_COMMENTS then
            local block_name = self:GetStartBlockName(cur_token);
            if block_name then            
                if tmp_file:GetSize() > 0 then
                    table.insert(tab,{
                        code = file_to_string(tmp_file),                    
                    });
                end
                tmp_file:SetSize(0);                       
                start_block_name = block_name;
            end

            local extra_name1,extra_name2 = self:GetExtraStartBlockName(cur_token);
            if extra_name1 and extra_name2 then
                if tmp_file:GetSize() > 0 then
                    table.insert(tab,{
                        code = file_to_string(tmp_file),
                    });
                end
                tmp_file:SetSize(0);
                start_extra_name = {
                    name1 = extra_name1,
                    name2 = extra_name2,
                }
            end
            
            local insert_point = self:GetInsertPointName(cur_token);
            if insert_point then
                if tmp_file:GetSize() > 0 then
                    table.insert(tab,{
                        code = file_to_string(tmp_file),
                    });
                end
                tmp_file:SetSize(0);
            end            
        end

        tmp_file:Puts(cur_token);
                
        if type == TOKEN_MULTI_LINE_COMMENTS or type == TOKEN_SINGLE_LINE_COMMENTS then        
            local block_name = self:GetEndBlockName(cur_token);
            if block_name and block_name == start_block_name then
                if tmp_file:GetSize() > 0 then
                    table.insert(tab,{
                        name = block_name,
                        code = file_to_string(tmp_file),                    
                    });                
                end
                tmp_file:SetSize(0);            
                start_block_name = nil;
            end           
            
            if start_extra_name then
                local extra_name1,extra_name2 = self:GetExtraEndBlockName(cur_token);
                if extra_name1 == start_extra_name.name1 and
                   extra_name2 == start_extra_name.name2
                then
                    if tmp_file:GetSize() > 0 then
                        table.insert(tab,{
                            extra_name = {
                                name1 = extra_name1,
                                name2 = extra_name2,
                            },
                            code = file_to_string(tmp_file),                    
                        });
                    end
                    tmp_file:SetSize(0);                       
                    start_extra_name = nil;
                end             
            end
            
            local insert_point = self:GetInsertPointName(cur_token);
            if insert_point then      
                if tmp_file:GetSize() > 0 then
                    table.insert(tab,{
                        insert_point = insert_point,
                        code = file_to_string(tmp_file),
                    });
                end
                tmp_file:SetSize(0);                       
            end            
        end
    end
    
    if tmp_file:GetSize() > 0 then
        table.insert(tab,{
            code = file_to_string(tmp_file),                    
        });                
    end
    
    lex_xx:Destroy();
    mf:Destroy();
    tmp:Destroy();
    file_ref:Destroy();    
    return tab;
end

function CodeSplitor:GetBlockName_Common(line,start_tag, end_tag, name)
    line:Seek(0);
    if not line:StartWith(start_tag,true,true) then
        return 
    end

    if not line:EndWith(end_tag,true,true) then
        return 
    end

    local mem = new_mem();

    line:Seek(string.len(start_tag));
    line:ReadString(mem);

    if mem:CStr() ~= name then
        return
    end
        
    local offset = line:GetOffset();
    local end_pos = line:SearchStr(end_tag,true,false);
    if end_pos < 0 then return end

    mem:SetSize(0);
    line:Seek(offset);
    line:Read(mem,end_pos - offset);
    mem:Trim();

    if mem:StrLen() > 0 then
        local ret = mem:CStr();
        mem:Destroy();
        return ret;
    end
end

function CodeSplitor:GetExtraBlockName_Common(line,start_tag, end_tag, name)
    line:Seek(0);
    if not line:StartWith(start_tag,true,true) then
        return 
    end

    if not line:EndWith(end_tag,true,true) then
        return 
    end

    local mem = new_mem();
    
    line:Seek(string.len(start_tag));
    line:ReadString(mem);

    if mem:CStr() ~= name then
        mem:Destroy();
        return
    end

    line:ReadString(mem);
    local name1 = mem:CStr();

    mem:SetSize(0);
    line:Read(mem,line:GetSize()-line:GetOffset()-string.len(end_tag));
    mem:Trim();
    if mem:StrLen() > 0 then
        local ret = mem:CStr();
        mem:Destroy();
        return name1,ret;
    end
end

function CodeSplitor:GetCppStartBlockName(line)
    return self:GetBlockName_Common(line,"/*##","##*/","Begin");
end

function CodeSplitor:GetCppEndBlockName(line)
    return self:GetBlockName_Common(line,"/*##","##*/","End");
end

function CodeSplitor:GetCppExtraStartBlockName(line)
    return self:GetExtraBlockName_Common(line,"/*@@","@@*/","Begin");
end

function CodeSplitor:GetCppExtraEndBlockName(line)
    return self:GetExtraBlockName_Common(line,"/*@@","@@*/","End");
end

function CodeSplitor:GetCppInsertPointName(line)
    return self:GetExtraBlockName_Common(line,"/*@@","@@*/","Insert");
end

function CodeSplitor:GetLuaStartBlockName(line)
    return self:GetBlockName_Common(line,"--##","##--","Begin");
end

function CodeSplitor:GetLuaEndBlockName(line)
    return self:GetBlockName_Common(line,"--##","##--","End");
end

function CodeSplitor:GetLuaExtraStartBlockName(line)
    return self:GetExtraBlockName_Common(line,"--@@","@@--","Begin");
end

function CodeSplitor:GetLuaExtraEndBlockName(line)
    return self:GetExtraBlockName_Common(line,"--@@","@@--","End");
end

function CodeSplitor:GetLuaInsertPointName(line)
    return self:GetExtraBlockName_Common(line,"--@@","@@--","Insert");
end


function CodeSplitor:GetStartBlockName(line)
    if self.m_code_type == "lua" then
        return self:GetLuaStartBlockName(line);
    else
        return self:GetCppStartBlockName(line);
    end
end

function CodeSplitor:GetEndBlockName(line)
    if self.m_code_type == "lua" then
        return self:GetLuaEndBlockName(line);
    else
        return self:GetCppEndBlockName(line);
    end
end

function CodeSplitor:GetExtraStartBlockName(line)
    if self.m_code_type == "lua" then
        return self:GetLuaExtraStartBlockName(line);
    else
        return self:GetCppExtraStartBlockName(line);
    end
end

function CodeSplitor:GetExtraEndBlockName(line)
    if self.m_code_type == "lua" then
        return self:GetLuaExtraEndBlockName(line);
    else
        return self:GetCppExtraEndBlockName(line);
    end
end

function CodeSplitor:GetInsertPointName(line)
    if self.m_code_type == "lua" then
        return self:GetLuaInsertPointName(line);
    else
        return self:GetCppInsertPointName(line);
    end
end