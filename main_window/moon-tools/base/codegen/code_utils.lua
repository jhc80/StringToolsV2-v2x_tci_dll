require("common")

function for_each_hint(hints,callback)
    local mem = new_mem();
    for _,h in ipairs(hints) do  
        mem:SetSize(0);
        mem:Puts(h);
        mem:Seek(0);
        if callback(mem,h) then
            break;
        end
    end
end

--mem maybe not from start--
function for_each_word(mem,callback)
    local tmp = new_mem();    
    while mem:ReadString(tmp) do        
        if callback(tmp:CStr(),tmp) then
            break;
        end        
    end
end

function set_code_switch_by_hint(hints, code_switch)
    if not hints then return end
    for_each_hint(hints,function(mem)        
        if mem:NextString()=="CodeSwitch" then        
            while not mem:IsEnd() do            
                local key = mem:NextString();
                local eq = mem:NextWord();
                if eq ~= "=" then
                    break;
                end 
                local value = mem:NextString();                
                code_switch[key] = (value == "true");
            end
        end    
    end);
end

-------------------------------------------------------------
-------------------------------------------------------------
function get_cpp_start_block_name(line)
    local ret = nil;
    for str in string.gmatch(line,"/*#Begin%s*(.-)%s*#%*/") do
        ret = str;
        break;
    end    
    return ret;
end

function get_cpp_end_block_name(line)
    local ret = nil;
    for str in string.gmatch(line,"/*#End%s*(.-)%s*#%*/") do
        ret = str;
        break;
    end    
    return ret;
end

function replace_block_in_cpp_file(in_file, block_name,rep_str)

    local do_not_replace = false;
    
    if not rep_str then
        do_not_replace = true;
    end
    
    local mem,mem_file = new_mem();    
    in_file:Seek(0);
    
    local block_start = false;
    
  	local mf,mf_file = new_memfile();

    while in_file:ReadLine(mem_file) do
        local str = mem:CStr();        

        if do_not_replace then             
            if  not (get_cpp_start_block_name(str) == block_name) and 
                not (get_cpp_end_block_name(str) == block_name)
            then
                mf_file:Puts(mem_file);
                mf_file:Puts(EOL);
            end        
        else
        
            if get_cpp_start_block_name(str) == block_name then
                block_start = true;            
            end
            
            if not block_start then
                mf_file:Puts(mem_file);
                mf_file:Puts(EOL);
            end
            
            if get_cpp_end_block_name(str) == block_name then
                block_start = false;    
                mf_file:Puts(rep_str);
            end
        end
    end
        
    in_file:SetSize(0);
    in_file:WriteFile(mf_file);    
end

function batch_replace_block_in_cpp_files(file_tab, block_name,rep_str)
    for _,file in pairs(file_tab) do
        replace_block_in_cpp_file(file,block_name,rep_str);       
    end
end