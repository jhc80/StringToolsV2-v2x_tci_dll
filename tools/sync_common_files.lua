require("tools_common");
require("make_file_list");



for_each_dll_projects(function(info)
    ClearFilesList();
    AddFolder(LUA_SOURCE_PATH,nil);
    CopyFilesTo(info.abs_lua_path,nil,LUA_SOURCE_PATH);
    
    ClearFilesList();
    AddFolder(SHARE_SOURCE_PATH,nil);
    CopyFilesTo(info.abs_share_path,nil,SHARE_SOURCE_PATH);
    
    ------    
    
    ClearFilesList();
    AddFolder(COMMON_SOURCE_PATH,nil);
    KeepFilesByFolder(COMMON_SOURCE_PATH,info.abs_common_path);    
    CopyFilesTo(info.abs_common_path,nil,COMMON_SOURCE_PATH);
    
    ClearFilesList();
    AddFolder(PLATFORM_SOURCE_PATH,nil);
    KeepFilesByFolder(PLATFORM_SOURCE_PATH,info.abs_platform_path);    
    CopyFilesTo(info.abs_platform_path,nil,PLATFORM_SOURCE_PATH);
    
    

end);

