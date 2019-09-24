require("tools_common");

function deploy_dll(folder,dll_name,dst_dll_name)
    local fullname = FileManager.ToAbsPath(
        folder.."/Release/"..dll_name
    );
    
    if not FileManager.IsFileExist(fullname) then        
        fullname = FileManager.ToAbsPath(
            folder.."/"..dll_name
        );        
    end
    
    if not FileManager.IsFileExist(fullname) then
        print("can not find dll file "..dll_name);
        return
    end
    
    FileManager.CopySingleFile(
        fullname,
        FileManager.ToAbsPath(DLL_DEPLOY_PATH.."/"..dst_dll_name),
        MODE_CHECKSAME|MODE_OVERWRITE|MODE_USE_LOG
    );
end

-------------------------------------------
for_each_dll_projects(function(info)
    deploy_dll(info.abs_path,info.src_dll_name, info.dll_name);
end);
