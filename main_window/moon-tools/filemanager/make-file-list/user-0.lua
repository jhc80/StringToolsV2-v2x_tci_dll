--要制作列表的目录--
the_folder = "Z:\\v2x\\sources\\HuaWei_ETSI_V2\\Sources\\1609_facility_r4.0_feature_huawei\\standard_ETSI\\v2x-lib\\src\\communication\\NetLayer";

--要保存的列表文件，如果为空就不保存--
save_file = "";

--是否递归搜索--
recursive = true;

--是否显示全路径--
full_path = false;

--是否以unix的方式显示路径名字--
unix_style = true;

--过滤器，返回false就不会出现在列表中--
function file_name_filter(info)
	return info.is_dir;
end

--如何打印的函数--
function how_to_print(info)
    local prefix = the_folder;
    
    if unix_style then
        info.full_name = string.gsub(info.full_name,"\\","/");
        prefix = string.gsub(the_folder,"\\","/");
    end

    if full_path then
        printnl(info.full_name);
    else
        local rpath = remove_path_prefix(info.full_name,prefix);
        printnl(rpath);
    end
end

