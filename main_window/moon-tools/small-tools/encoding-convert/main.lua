require("common");

local list = App.LoadText();
App.ClearScreen();
----------------------------------------------------
require("user");

function convert_encoding(filename)
    if from_encoding == to_encoding then
        return;
    end

    local infile = new_file(filename,"rb");
    if not infile then
        printfnl("open file %s fail.",filename);
        return;
    end

    if infile:GetSize() <= 0 then
        infile:Destroy();
        return;
    end

    if not FileManager.IsTextFile(infile) then
        infile:Destroy();
        return;
    end

    local mf = new_memfile();
    
    FileManager.EncodingConvert(from_encoding,to_encoding,infile,mf);

    if mf:WriteToFile(filename) > 0 then
        printfnl("convert %s ok.",filename);
    end

    mf:Destroy();
    infile:Destroy();
end

for_each_line(list,function(line)
    line:Trim();
    if line:StrLen() > 0 then
        convert_encoding(line:CStr());
    end
end);