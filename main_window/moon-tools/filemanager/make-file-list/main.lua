require("common");
require("user");

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
