require("common");
require("user");
require("bson");
require("win32");
require("simple_file_client")

local UI_WND_HEIGHT=100;
local EVENT_NEW_CLIENT = 1;
local EVENT_CONNECTED = 1;
local EVENT_STOP = 2;

local g_cur_remote_dir="/"
local g_cur_local_dir = download_path;

App.ClearScreen();
App.StartNet();
printfnl("Download path is: %s",g_cur_local_dir);

App.ShowEmbeddedUIWindow(UI_WND_HEIGHT);
local hwnd = App.GetHWnd(HWND_EMBEDDED_UI);

if not hwnd then
    printnl("can not find embedded ui window");
    return
end

local _,_,UI_WND_WIDTH = Win32.GetClientRect(hwnd);

local editbox = EditBox.new();
editbox:SetParent(hwnd);

editbox:AddStyle(
    ES_NOHIDESEL |
    WS_VSCROLL|ES_AUTOVSCROLL |
    WS_BORDER
);

editbox:Create();
editbox:SetStockFont(SYSTEM_FIXED_FONT);

function relayout(width,height)
    local btn_width ,btn_height = 0, height-40;
    editbox:MoveWindow(
        10,10,
        width-btn_width-50,height-20
    );    
end

if as_server  then
	App.StartMessageCenter(port);
	printfnl("start message center on port %d",port);
end

local cur_cmd_line = nil;

function print_list(list)
	
	for k,v in ipairs(list) do
		if v.is_dir then
			printfnl("<%s>", v.name);
		end
	end

	for k,v in ipairs(list) do
		if not v.is_dir then
			printfnl("%s\t\t\t%d",v.name,v.size);
		end
	end
end

function parse_command_line(cmd_line)
	cmd_line:Seek(0);
	local cmd = cmd_line:NextString();
	local param_str = new_mem(32*1024);
	cmd_line:ReadLeftStr(param_str,true);
	return cmd, string.trim(param_str:CStr());
end

function do_list_file(thread,file_client,params)	
	if not params or params == "" then
		params = g_cur_remote_dir;
	end

	local list = file_client:List(params);
	if list then
		print_list(list);
	end
end

function do_run(thread,file_client,params)	
	file_client:RunCommand(params,function(ret,val)
		print_table(val);
	end);
end

function do_get(thread,file_client,params)
	local remote_file = FileManager.ToAbsPath(params,g_cur_remote_dir);
	
	local local_file = FileManager.ToAbsPath(
		FileManager.SliceFileName(remote_file,FN_FILENAME),
		g_cur_local_dir
	);
	
	start_pull_thread(file_client,remote_file,local_file);
end

function do_cd(thread,file_client,params)
	if not params or params == "" or params=="." then
		printfnl("current remote dir is '%s'",g_cur_remote_dir);
		return
	end
		
	local done = false;
	file_client:ChangeDir(params,function(ret,val)
		if ret == E_OK then
			if val.success then
				g_cur_remote_dir = val.cur_dir;
				printfnl("change remote dir to %s",val.cur_dir);
			else
				printfnl("change remote dir to %s fail.",val.cur_dir);
				printfnl("current dir is %s",g_cur_remote_dir);
			end
		end
		done = true;
	end);
	
	while not done do
		thread:Sleep(100);
	end
end

function do_cls(thread,file_client,params)
	App.ClearScreen();
end

function do_run(thread,file_client,params)
	local command = params;
    file_client:RunCommand(command,function(ret,val)
		print("run cmd:\""..command.."\"");
		printnl(ret==1 and " success" or " fail");
		if ret == 1 then
			printfnl("the result is %d",val.result)
		end
	end);
end

function do_put(thread,file_client,params)
	local local_file_name = FileManager.ToAbsPath(params);
	local is_dir = false;
	if FileManager.IsDirExist(local_file_name) then
		is_dir = true;
	elseif not FileManager.IsFileExist(local_file_name) then
		printfnl("local file or dir '%s' is not exist",local_file_name);
		return
	end
	
	local file_name = FileManager.SliceFileName(local_file_name,FN_FILENAME);
	local remote_file_name = FileManager.ToAbsPath(g_cur_remote_dir.."/"..file_name);
	
	if not is_dir then	
		 if not file_client:PushBigFile(local_file_name,remote_file_name) then
			printfnl("push file fail %s",local_file_name);
		else
			printfnl("send %s ok",local_file_name);
		end   
	else
	    local file_list = {};
        FileManager.SearchDir(local_file_name,true,function(info)
                if info.event == EVENT_SINGLE_FILE then
                    table.insert(file_list,info.full_name);
                end
        end);
			
		for _,v in ipairs(file_list) do
			local rfile = remote_file_name.."/"..remove_path_prefix(v,local_file_name);
			if not file_client:PushBigFile(v,rfile) then
				printfnl("push file fail %s",v);
			else
				printfnl("send %s ok",v);                    
			end
		end       			
	end
end

function main_thread(thread)
	local file_client = SimpleFileClient.new(thread);
	if as_server then
		file_client:InitServerSidePeer();        
	else
		file_client:InitClientSidePeer(server,port);
	end

	file_client:SetName("string-tools-client");
	file_client:SetDestPeerName("simple-file-server");
	file_client:Start();
	
	do_cd(thread,file_client,"/");
	
	while true do
			if cur_cmd_line then	
				local cmd,params = parse_command_line(cur_cmd_line);
				if cmd == "ls" then
					do_list_file(thread,file_client,params);
				elseif cmd == "run" then
					do_run(thread,file_client,params);
				elseif cmd == "get" then
					do_get(thread,file_client,params);
				elseif cmd == "cd" then
					do_cd(thread,file_client,params);
				elseif cmd == "cls" or cmd == "clear" then
					do_cls(thread,file_client,params);
				elseif cmd == "pwd" then
					do_cd(thread,file_client,"");
				elseif cmd == "run" then
					do_run(thread,file_client,"");
				elseif cmd == "put" then
					do_put(thread,file_client,params);
				elseif cmd then
					printfnl("unknown command: %s",cmd);
				end
				printnl("----------------------------------------------");
				cur_cmd_line = nil;
			end
			thread:Sleep(500);
	end
	
end

function on_return_pressed()
	local text = new_mem(32*1024);
	editbox:GetText(text);
	cur_cmd_line = text;
	local len = text:GetSize();
	editbox:SetText("");
end

App.SetOnAppEvent(function(e,data)
    local msg;
    
    if e == APP_EVENT_EMBEDDED_UI_WINDOW_RESIZED or 
       e == APP_EVENT_EMBEDDED_UI_WINDOW_MESSAGE 
    then
		local bson = Bson.new();
		bson:LoadBson(data);
		msg = BsonToObject(bson);		
    end

	if e == APP_EVENT_EMBEDDED_UI_WINDOW_RESIZED then			
        relayout(msg.right,msg.bottom);
	end
end);

Win32.SetOnWindowMessage(function(hwnd,message,wparam,lparam)
    if hwnd == editbox:GetHWnd() and message == WM_CHAR then
        if wparam == VK_RETURN then
			on_return_pressed();
		end
    end
end);

local function size_string(size)
	if size < 1024 then
		return size;
	end
	
	if size < (1024*1024) then
		return string.format("%.03f KB",(size/1024.0));
	end
	
	if size < (1024*1024*1024) then
		return string.format("%.03f MB",size/(1024.0*1024.0));
	end
	
	return string.format("%.03f GB",size/(1024.0*1024.0*1024.0));
end

function parallel_pull_files(thread,file_client,all_pull_files)
    local pending = 0;
    while #all_pull_files > 0 do
        if pending < 20 then
            local head = all_pull_files[1];
            table.remove(all_pull_files,1);
            pending = pending + 1;
            file_client:PullFile(head.remote_file,head.local_file,function(error)
                if error then
                    printfnl("~~ pull file %s fail.~~",head.remote_file);
                else
                    printfnl("pull file %s ok.",head.remote_file);
                end                
                pending = pending - 1;
            end);
        else
            thread:Sleep(1);
        end
    end
	
    while pending > 0 and not file_client:IsClosedPermanently() do
		local size = file_client:GetCurPullSize();
		App.SetStatusText(1,size_string(size));
        thread:Sleep(200);
    end
	
end

function pull_thread(thread,file_client,remote_file,local_file)
	local local_dir = local_file;
	local remote_dir = nil;
    local list = file_client:List(remote_file);
	if list then
		remote_dir = remote_file;
	else
		if FileManager.IsDirExist(local_file) then
			local name = FileManager.SliceFileName(remote_file,FN_FILENAME);
			local_file = FileManager.ToAbsPath(local_file.."/"..name);
		end
	end

	local all_pull_files = {};
	function will_pull_file(_remote_file,_local_file)
		table.insert(all_pull_files,{
			remote_file = _remote_file,
			local_file = _local_file,
		});
	end
	
	function pull_folder(thread,_local_dir,_remote_dir)            
		local file_list = file_client:List(_remote_dir);
		if not file_list then
			return
		end
		for _, info in ipairs(file_list) do
			local next_file = _remote_dir .."/"..info.name;
			if info.is_dir then          
				pull_folder(thread,_local_dir,next_file);                    
			else
				local _local_file = FileManager.ToAbsPath(
					_local_dir.."/"..remove_path_prefix(next_file,remote_dir)
				);
				will_pull_file(next_file,_local_file);
			end
		end
	end
	
	if not remote_dir then
		will_pull_file(remote_file,local_file);
	else
		printfnl("listing folder %s",remote_dir);
		pull_folder(thread,local_dir,remote_dir);
	end
	
	printfnl("total %d files.",#all_pull_files);
	parallel_pull_files(thread,file_client,all_pull_files);
	printnl("all done");
	g_pull_co = nil
end

function start_pull_thread(file_client, remote_file,local_file)
	if g_pull_co then
		printnl("already pulling");
		return
	end
	g_pull_co = CoThread.new(1);
	g_pull_co:Start(pull_thread,file_client,remote_file,local_file);
end

co = CoThread.new(1);
co:Start(main_thread);
relayout(UI_WND_WIDTH,UI_WND_HEIGHT);
App.MainLoop();

