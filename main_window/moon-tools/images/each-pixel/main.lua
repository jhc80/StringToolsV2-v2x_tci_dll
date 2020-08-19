require("common");

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();
App.ClearScreen();
require("user");

function rgba(color)
    local r = color&0xff;
    local g = (color>>8) & 0xff;
    local b = (color>>16)&0xff;
	local a = (color>>24)&0xff;
    return r,g,b,a;
end

function color(r,g,b,a)
    return  (r&0x000000ff) 
        | ((g << 8)&0x0000ff00)
        | ((b << 16)&0x00ff0000)
        | ((a << 24)&0xff000000);
end

function convert_image(fn)
	local img = XImage.new();
	if not XImageHelper.LoadImage(fn,img) then
		printfnl("load image %s fail",fn);
		return
	end
	local w = img:GetWidth();
	local h = img:GetHeight();
	
	if w <= 0 or h <= 0 then
		return
	end
	
	local new_img = XImage.new();
	new_img:Create(w,h,24,0);
	new_img:AlphaCreate();
	
	for y = 0,h-1,1 do	
		for x=0,w-1,1 do
			local c = img:GetPixelColor(x,y,true);
			local r,g,b,a = convert_pixel(x,y,c);
			new_img:SetPixelColor(x,y,color(r,g,b,a),true);
		end
	end
	
	XImageHelper.SaveImage(new_img,fn);	
	img:Destroy();
	new_img:Destroy();
	return true;
end

for_each_line(mem_text_file,function(line)
	if convert_image(line:CStr()) then
		printfnl("convert %s ok",line:CStr());
	end
end);
