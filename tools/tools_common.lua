require("common");
require("all_projects");

function get_path_from_env(env_name,rpath)
    if not rpath then
        rpath = "";
    end
    local env = os.getenv(env_name);
    if env then
        return FileManager.ToAbsPath(env.."/"..rpath);
    end
end

ROOT_PATH = get_path_from_env("ROOT_PATH");
DLL_DEPLOY_PATH = get_path_from_env("DLL_DEPLOY_PATH");
LUA_SOURCE_PATH = get_path_from_env("MAIN_WINDOW_PATH","lua");
COMMON_SOURCE_PATH = get_path_from_env("MAIN_WINDOW_PATH","common");
PLATFORM_SOURCE_PATH = get_path_from_env("MAIN_WINDOW_PATH","platform");
SHARE_SOURCE_PATH = get_path_from_env("MAIN_WINDOW_PATH","share");

function for_each_dll_projects(callback)
    for _, info in ipairs(g_all_dll_projects) do
        if not info.abs_path then
            info.abs_path = FileManager.ToAbsPath(ROOT_PATH.."/"..info.path);
        end
        
        for k,v in pairs(info.sub_dirs) do
            local new_k = "abs_"..k;            
            if not info[new_k] then                
                info[new_k] = FileManager.ToAbsPath(info.abs_path.."/"..v);                
            end        
        end        
        
        callback(info);
    end
end
