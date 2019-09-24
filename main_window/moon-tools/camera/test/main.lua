require("common");
require("user");
require("webcamera");

App.ClearScreen();

local camera = WebCamera.new();
local all_devices = camera:GetAllDeviceNames();

if gif_file ~= "" then
    gif_file = FileManager.ToAbsPath(gif_file);
    has_gif = true;
end

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

local i = 0;
local mem = Mem.new();
local tmp_img = XImage.new();

local mf = new_memfile();

local gif_encoder = GifEncoder.new();
if has_gif then
    gif_encoder:Begin(gif_file);
end

local frame = 0;
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
    
    if has_gif then        
        tmp_img:Resample(width*scale_x,height*scale_y);        
        tmp_img:DecreaseBpp(8);                
        gif_encoder:AddFrame(tmp_img);
    end
        
	Screen.DrawImage(tmp_img,0,0);    
	Screen.Redraw();
        
    App.SetStatusText(1,frame);
    frame = frame+1;
    
	App.Sleep(delay_per_frame);
end

App.SwitchToPageText();

if not has_gif then
    return
end

printfnl("save to %s...",gif_file);
gif_encoder:End();
printnl("ok");

