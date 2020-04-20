require("common");
require("user");
require("webcamera");
require("win32");
require("cothread");
require("bson");

App.ClearScreen();

local UI_WND_HEIGHT=150;


App.ShowEmbeddedUIWindow(UI_WND_HEIGHT);
local hwnd = App.GetHWnd(HWND_EMBEDDED_UI);

if not hwnd then
    printnl("can not find embedded ui window");
    return
end

local _,_,UI_WND_WIDTH = Win32.GetClientRect(hwnd);

local button = Button.new();
button:SetParent(hwnd);
button:Create();
button:SetStockFont(SYSTEM_FIXED_FONT);
button:SetText("拍照(SPACE)");
button:MoveWindow(50,(UI_WND_HEIGHT-50)/2,120,50);

local take_phote = false;
function on_button_click()
	take_phote = true;
end

local is_space_key_down = false;
function process_key_event()				
	if Win32.GetAsyncKeyState(VK_SPACE) ~= 0 then
		if not is_space_key_down then
			is_space_key_down = true;
			take_phote = true;
		end
	else
		is_space_key_down = false;
	end
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
    
    if e == APP_EVENT_EMBEDDED_UI_WINDOW_MESSAGE then        
        if msg.message == WM_COMMAND then
            if button:IsMyCommand(msg.wparam) then
                on_button_click();
            end
        end    
    end    
end);
-----------------------------------------------------------------

local camera = WebCamera.new();
local all_devices = camera:GetAllDeviceNames();

if #all_devices <= 0 then
    printnl("no device found.");
    return;
end

for _,name in ipairs(all_devices) do
    printnl(name);
end

if not camera:SetActiveDevice(active_device) then
    printnl("set active device fail.");
    return;
end

if not camera:Start() then
    return;
end

App.Sleep(1000);

App.SwitchToPageImage();

local width = camera:GetPixelWidth();
local height = camera:GetPixelHeight();

Screen.Create(width*scale_x,height*scale_y);

function main_thread(thread)
	local mem = Mem.new();
	local tmp_img = XImage.new();
	local index = 0;
	local mf = new_memfile();
	while not App.UserStopped() do
		if not camera:TakePictureBmp() then
			printnl("TakePictureBmp fail.");
			break;
		end
		local ptr,size = camera:GetFrameData();
		mem:Destroy();
		mem:SetRawBuf(ptr,size,true);    
		local file_ref = mem:FileBase();   
		XImageHelper.LoadImage(file_ref,tmp_img);
			
		Screen.DrawImage(tmp_img,0,0);    
		
		if take_phote then		
			local fn = get_photo_file_name(index);			
			
			if XImageHelper.SaveImage(Screen:GetBackImage(),fn) then
				printfnl("save photo to %s success",fn);
				App.SetStatusText(1,fn);
				index = index+1;
			else
				printfnl("save photo to %s fail",fn);
			end
			take_phote = false;	
		end

		process_key_event();
		Screen.Redraw();
		thread:Sleep(20);
	end

	App.SwitchToPageText();
end

co = CoThread.new(1);
co:Start(main_thread);
App.MainLoop();

