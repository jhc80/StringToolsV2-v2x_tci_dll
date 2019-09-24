local user_module = "user-"..App.GetCurrentUser();

local user_file = App.GetSelfPath(user_module..".lua");

if not FileManager.IsFileExist(user_file) then
    user_module = "default";
end

require(user_module);
