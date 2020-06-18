require("common");
require("user");
require("bson");
require("win32");
require("remote_desktop_server");

local hdc = Win32.GetDC(0);
local r = Win32.GetWindowRect(Win32.GetDesktopWindow());
local screen_width = r[3];
local screen_height = r[4];
local img = XImage.new();

jpeg_file = new_mem(4*1024*1024);

function take_screen_shot(ratiox, ratioy,quality)
	if ratiox >  1 then ratiox = 1 end
	if ratioy >  1 then ratioy = 1 end
	if quality > 100 then quality = 100 end

	XImageHelper.CreateImageFromHdc(img,0,0,
		screen_width*ratiox,screen_height*ratioy,
		hdc,0,0,screen_width,screen_height);
	img:SetJpegQualityF(quality);	
	jpeg_file:SetSize(0);	
	XImageHelper.SaveImage(img,"jpg",jpeg_file);	
end


App.ClearScreen();
App.StartNet();

local rd_server = RemoteDesktopServer.new();

if as_client then	
	rd_server:InitClientSidePeer(server,port);
else	
	App.StartMessageCenter(port,true);
	printfnl("start message center on port %d",port);
	rd_server:InitServerSidePeer();        
end

rd_server:SetName(peer_name);
rd_server:Start();

App.MainLoop();

