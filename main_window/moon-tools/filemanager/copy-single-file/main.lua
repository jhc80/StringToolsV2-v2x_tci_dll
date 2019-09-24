require("common");
require("user");

App.ClearScreen();


if in_file == "" then
    return
end

if out_file == "" then
    return
end

print("copying...");    
FileManager.CopySingleFile(
    in_file,out_file,
    in_start,copy_size,
    out_start,
    MODE_OVERWRITE|MODE_PART_COPY
);
printnl("ok.");