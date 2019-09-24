function is_empty_char(ch)
    return ch == 32 or ch == 9 or ch == 10 or ch == 13;
end

function split_into_blocks(c_file)
    local lex_xx = LexerCpp.new();
    local lex = lex_xx:Lexer();    
    
    lex:LoadFile(c_file);
      
	local bracket_big = 0;
	local bracket_small = 0;
    
    local mf,mf_file = new_memfile();
    local tmp, tmp_file = new_memfile();
    local blocks = {};
    
    local function add_tmp_text(clear)
        if tmp_file:GetSize() > 0 then
            table.insert(blocks,file_to_string(tmp_file));
        end
        if clear then
            tmp_file:SetSize(0);
        end
    end
    
    local function add_cur_token(clear)
        if mf_file:GetSize() > 0 then
            table.insert(blocks,file_to_string(mf_file));
        end
        if clear then
            mf_file:SetSize(0);
        end
    end
    
    while not lex:IsEnd() do
        mf_file:SetSize(0);
        local type = lex_xx:NextToken(mf_file);        
        local cur_token = mf_file;        
        
        if type == TOKEN_PUNCTUATION then
            local ch = cur_token:CharAt(0);
            if ch == 40 then -- '('
                bracket_small = bracket_small + 1;
            elseif ch == 41 then --')'
                bracket_small = bracket_small - 1;
            elseif ch == 123 then --'{'
                if bracket_big == 0 then
                    add_tmp_text(true);
                end
                bracket_big = bracket_big + 1;
            elseif ch == 125 then --'}]
                bracket_big = bracket_big - 1;
                if bracket_big == 0 then
                    tmp_file:Puts(cur_token);
                    add_tmp_text(true);
                    goto continue;
                end
            elseif ch == ';' then
                if bracket_big == 0 and bracket_small == 0 then
                    tmp_file:Puts(cur_token);
                    add_tmp_text(true);
                    goto continue;
                end                
            end            
        end    
        
        if bracket_big == 0 then        
            if type == TOKEN_PREPROCESS then
                add_tmp_text(true);
                add_cur_token();
            elseif type == TOKEN_SINGLE_LINE_COMMENTS or type == TOKEN_MULTI_LINE_COMMENTS then
				local hit_block_end;
                
				if tmp_file:GetSize() <= 0 then
					hit_block_end = true;                    
				elseif tmp_file:CharAt(0) ==  35 then --'#'
					hit_block_end = true;
                end
                
				local ch = tmp_file:GetLastChar(0);
				if ch == 125 or ch == 59 or is_empty_char(ch) then
					hit_block_end = true;
                end
                
				if hit_block_end then
					add_tmp_text(true);
                    add_cur_token();
				else
					tmp_file:Puts(cur_token);
                end
            else
                tmp_file:Puts(cur_token);
            end
        else
            tmp_file:Puts(cur_token);
        end
    ::continue:: end
    
    add_tmp_text();
    
    return blocks;
end

local keywords = {
    "if","else","while","for","do","return","switch","case","break",
    "struct","typedef","int32_t","float","double","char","unsigned","signed",
    "short","const","static","try","catch"
};

function is_function_block(block_text)
    local _,block_file = new_memfile();
    block_file:Puts(block_text);
    
    block_file:Seek(0);
    block_file:SkipEmptyChars();
    
    local ch = block_file:Getc();
	if ch == 35 or ch == 47 then
		return;
    end
    
    local lex_xx = LexerCpp.new();
    local lex = lex_xx:Lexer();
    
    lex:LoadFile(block_file);
    
    local hit = false;
    local bracket = 0;
    local mf,mf_file = new_memfile();
    
    while not lex:IsEnd() do
        mf_file:SetSize(0);
        local type = lex_xx:NextToken(mf_file);        
        local cur_token = mf_file;        
        
        local ch = mf_file:CharAt(0);
        
        if type == TOKEN_PUNCTUATION then
            if ch == 40 then --'('
                bracket = bracket + 1;
                hit = true;
            elseif ch == 41 then --')'
                bracket = bracket - 1;
            end
            
            if ch == 61 then --'='			
				if bracket == 0 then
					return
                end
            elseif ch == 59 then --';'
                return
			end
        end        
    end
    
    if not hit then return end
    if bracket ~= 0 then return end
    return true;
end

function remove_class_prefix(text)
    local mem, mem_file = new_mem();
    mem_file:Puts(text);
    
	local buf, buf_file = new_mem();
    
	mem_file:Seek(0);
	local pos2 = mem_file:SearchStr("::",false,false);
	if pos2 < 0 then return text end

	pos2 = pos2 + 2;

	mem_file:Seek(pos2);
	mem_file:ReadString_Reverse(buf_file);
	local pos1 = mem_file:GetOffset();

	mem_file:Seek(pos1);
	mem_file:Delete(pos2-pos1);

	return mem:CStr();
end
