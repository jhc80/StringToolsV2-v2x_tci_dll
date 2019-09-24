require("common");
require("win32");
require("user");

function rgb(color)
    local r = color&0xff;
    local g = (color>>8) & 0xff;
    local b = (color>>16)&0xff;
    return r,g,b;
end

App.ClearScreen();
App.SwitchToPageImage();

local hdc = Win32.GetDC(0);

local last_color;
local last_x,last_y;

Screen.Create(200,200);

while true do
	local x,y = Win32.GetCursorPos();
    local color = Win32.GetPixel(hdc,x,y);        
    
    if color ~= last_color or last_x ~= x or last_y ~= y then    
        last_color = color;
        last_x = x;
        last_y = y;
        how_to_print(x,y,color);   
        Screen.Clear(color);
        Screen.Redraw();
        
        App.SetStatusText(2,
            string.format("rgb(%d,%d,%d)",rgb(color))
        );
    end    
    
    if Win32.GetAsyncKeyState(VK_ESCAPE) ~= 0 then
        break;
    end
    
	App.Sleep(10);
end


App.SwitchToPageText();
