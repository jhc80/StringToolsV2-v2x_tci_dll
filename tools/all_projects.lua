g_common_sub_dirs={
    lua_path="lua",
    common_path="common",
    platform_path="platform",
    share_path = "share",
}

g_all_dll_projects ={
    {
        path="test_dll",
        dll_name="test.dll",
        src_dll_name="dll.dll",        
        sub_dirs = g_common_sub_dirs,
    },{
        path="asn1_dll",        
        src_dll_name="test.dll",
        dll_name="asn1parser.dll",
        sub_dirs = g_common_sub_dirs,
    },{
        path="camera_dll",
        dll_name="webcamera.dll",
        src_dll_name="dll.dll",        
        sub_dirs = g_common_sub_dirs,
    }
};
