require("common")
require("win32")

local mem_text = App.LoadText();
App.ClearScreen();
----------------------------------------------------
require("user");
----------------------------------------------------
function is_comb_keys_down(comb_keys)
    for _,key in ipairs(comb_keys) do
        if Win32.GetAsyncKeyState(key) == 0 then
            return false;    
        end
    end
    return true;
end
----------------------------------------------------
function run_command(cmd,params)
    if not params then
        params = "";
    end

    local path = FileManager.SliceFileName(cmd,FN_PATH);
    if path ~= "" then
        FileManager.ChangeDir(path);
    end
    local cmd = "\""..cmd.."\" "..params;
    printnl("run:"..cmd);
    os.execute(cmd);    
end

while true do
    for _, info in ipairs(hotkey_table) do
        local comb_keys = info[1];
        local func = info[2];

        if is_comb_keys_down(comb_keys) then
            if not info.is_key_down then
                info.is_key_down = true;
                func();
            end
        else
            info.is_key_down = false;
        end
    end
    App.Sleep(50);
end