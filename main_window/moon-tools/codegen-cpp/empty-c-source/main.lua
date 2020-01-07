require("common");

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();

require("user");
App.ClearScreen();

function code_h(str)
    printfnl("#ifndef %s",ifdef_name(str));
    printfnl("#define %s",ifdef_name(str));
    
	printfnl("");
    printfnl(common_includes_h());
    
	if cplusplus then
		printfnl("#ifdef __cplusplus");
		printfnl("extern \"C\"{");
		printfnl("#endif");
		printfnl("");
		printfnl("#ifdef __cplusplus");
		printfnl("}");
		printfnl("#endif");
		printfnl("");
	end
	
    
    printfnl("#endif");    
end

function code_cpp(str)
    printfnl("#include \"%s.h\"",to_file_name(str));
    printfnl(common_includes_cpp());
    printfnl("");    
end

for_each_line(mem_text_file,function(line)
	local str = line:CStr();    
    local file_name = nil;
    if save_path ~= "" then
        file_name = FileManager.ToAbsPath(save_path.."/"..to_file_name(str)..".h");
        App.ClearBuffer();
    end
    code_h(str);
    if file_name then
        if App.SaveBuffer(file_name) then
            printfnl("save to %s ok.",file_name);
        else
            printfnl("fail to save %s.",file_name);
        end
    end
        
    local file_name = nil;
    if save_path ~= "" then
        file_name = FileManager.ToAbsPath(save_path.."/"..to_file_name(str)..".cpp");
        App.ClearBuffer();
    end
	printnl("");
    code_cpp(str);
    if file_name then
        if App.SaveBuffer(file_name) then
            printfnl("save to %s ok.",file_name);
        else
            printfnl("fail to save %s.",file_name);
        end		
    end
	return true; --only first line
end);

