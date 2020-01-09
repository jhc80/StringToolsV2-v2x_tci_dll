require("common");
require("user");
require("bson");
require("win32");
require("simple_file_client")

local UI_WND_HEIGHT=150;
local EVENT_NEW_CLIENT = 1;
local EVENT_CONNECTED = 1;
local EVENT_STOP = 2;

App.ClearScreen();
App.StartNet();

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
    ES_MULTILINE|ES_NOHIDESEL |
    WS_VSCROLL|ES_AUTOVSCROLL |
    ES_AUTOHSCROLL|ES_WANTRETURN |
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

local cur_list_file = "/";

function print_list(list)
	for k,v in ipairs(list) do
	
		if v.is_dir then
			printfnl("<%s>", v.name);
		else
			printfnl("%s\t\t\t%d",v.name,v.size);
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
	
	while true do
			if cur_list_file then			
				local list = file_client:List(cur_list_file);
				if list then
					App.ClearScreen();
					print_list(list);
				else
					App.ClearScreen();
				end
				cur_list_file = nil;
			end
			thread:Sleep(500);
	end
	
end

function on_return_pressed()
	local text = new_mem();
	editbox:GetText(text);
	text:Seek(0);
	cur_list_file = text:NextLine();
	editbox:SetText(cur_list_file);
	local len = string.len(cur_list_file);
	editbox:SetSel(len,len);
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



co = CoThread.new(1);
co:Start(main_thread);

relayout(UI_WND_WIDTH,UI_WND_HEIGHT);
App.MainLoop();

