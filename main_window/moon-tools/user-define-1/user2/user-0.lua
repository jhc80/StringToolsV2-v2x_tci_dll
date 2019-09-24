App.ClearScreen();

App.ClearScreen();

local hwnd_desktop = Win32.GetDesktopWindow();

local hdc_desktop = Win32.GetDC(hwnd_desktop);

local img = XImage.new();
img:CreateFromHdc(hdc_desktop);

printnl(img:GetWidth(),img:GetHeight());