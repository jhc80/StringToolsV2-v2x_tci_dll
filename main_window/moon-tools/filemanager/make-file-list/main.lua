require("common");
require("user");

function split(s, p)
    local rt= {}
    string.gsub(s, '[^'..p..']+', function(w) 
		rt[w] = 1;
	end);
    return rt
end

local exts_table={};
function in_ext_list(exts, info)
	if string.len(info.ext) > 0 and not info.is_dir then
		if not exts_table[exts] then
			exts_table[exts] = split(exts,",");
		end
		if exts_table[exts] then
			return exts_table[exts][info.ext];
		end
	end
end

App.ClearScreen();

if the_folder=="" then
    return;
end

the_folder = FileManager.ToAbsPath(the_folder).."\\";

if save_file~="" then
    App.StopBuffer();
end

FileManager.SearchDir(the_folder,recursive,function(info)
    if info.event == EVENT_END_DIR then
        return
    end
    
    local ext = FileManager.SliceFileName(info.file_name,FN_EXT);
    info.ext = ext;
    if file_name_filter(info) then
        how_to_print(info);
    end
end);

if save_file~="" then
    App.SaveBuffer(save_file);
    App.ClearScreen();
    App.StartBuffer();    
    printnl("save to "..save_file);
end
