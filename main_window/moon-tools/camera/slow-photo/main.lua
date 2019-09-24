require("common");
require("user");

require("webcamera");
App.ClearScreen();

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

if delay < 100 then delay = 100 end
local index = 1;

App.SwitchToPageImage();

local width = camera:GetPixelWidth();
local height = camera:GetPixelHeight();

Screen.Create(width*1.2,height);

local i = 0;
local mem = Mem.new();
local now_img = XImage.new();
local old_img = XImage.new();
local diff_img = XImage.new();

while true do
	if not camera:TakePictureBmp() then
        printnl("TakePictureBmp fail.");
        break;
    end
    
	local ptr,size = camera:GetFrameData();
	mem:Destroy();
	mem:SetRawBuf(ptr,size,true);
    
	XImageHelper.LoadImage(mem:FileBase(),now_img); 
        
    if now_img:GetWidth() ~= old_img:GetWidth() then
        old_img:Copy(now_img);        
    end

    local similarity = XImageHelper.CalcuSimilarity(now_img,old_img,threshold,diff_img);
    
    if similarity < min_similarity then
        old_img:Copy(now_img);
        Screen.Clear(0xffffffff);
    end
    	
    now_img:QIShrink(width*0.5,height*0.5,now_img);
    diff_img:QIShrink(width*0.5,height*0.5,diff_img);
    
    Screen.DrawImage(now_img,0,0);
    Screen.DrawImage(diff_img,width*0.5+20,0);
    
    Screen.Redraw();
    
    if similarity < min_similarity then
        local file_name = FileManager.ToAbsPath(
            save_path.."/"..create_file_name(index)
        );    
        index = index + 1;    
        if XImageHelper.SaveImage(now_img,file_name) then
            printfnl("save %s ok",file_name);
        else
            printfnl("fail to save %s",file_name);
            break;
        end
        App.Sleep(delay);
        Screen.Clear(0);
    end
    
	App.Sleep(20);
end
