require("common");
require("user");
require("asn1parser");
require("lua_to_js");

local mem_text = App.LoadText();
local mem_text_file = mem_text:FileBase();

App.ClearScreen();

local lua_str = nil;

if not convert_files then
    mem_text_file:Trim();
    if mem_text_file:StrLen() > 0 then
        lua_str = ASN1.ParseString(mem_text:CStr());
    end
else
    local filelist = {};
    for_each_line(mem_text_file,function(line)
        line:Trim();
        local str = line:CStr();
        if line:StrLen() > 0 then
            table.insert(filelist,FileManager.ToAbsPath(str));
        end
    end);

    lua_str = ASN1.ParseFileList(filelist);
end

if not lua_str then
    return
end

if table_prefix ~= "" then
    print(table_prefix);
end
    
if not convert_to_javascript then
    if save_file_name ~= "" then
        printnl(lua_str);
        App.SaveBuffer(save_file_name);
        printnl("save to file "..save_file_name);    
    else
        printnl(lua_str);
    end
else
    local lua_table = string_to_table(lua_str);
    if not lua_table then
        printnl("can not load lua table");
        return
    end
    
    local js_obj = lua_table_to_js(lua_table);
    
    if save_file_name ~= "" then
        printnl(js_obj);
        App.SaveBuffer(save_file_name);
        printnl("save to file "..save_file_name);    
    else
        printnl(js_obj);
    end
    
end


