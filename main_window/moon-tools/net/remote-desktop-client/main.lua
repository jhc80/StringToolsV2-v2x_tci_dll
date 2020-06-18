require("common");
require("user");
require("bson");
require("win32");
require("remote_desktop_client");

App.ClearScreen();
App.StartNet();

local rd_client = RemoteDesktopClient.new();

if as_server then	
	App.StartMessageCenter(port,true);
	printfnl("start message center on port %d",port);
	rd_client:InitServerSidePeer();        	
else	
	rd_client:InitClientSidePeer(server,port);
end

rd_client:SetName(peer_name);
rd_client:SetDestPeerName(server_peer_name);
rd_client:Start();

App.SwitchToPageImage();

function main_thread(thread)
	local resized = false;
	
	while true do
		local done = false;
		local ret = rd_client:TakeScreenShot(ratiox,ratioy, quality,
			function(ret,val)
				if ret == E_OK then
					local bin = val.jpeg._binary_;
					local img = XImage.new();
					XImageHelper.LoadImage(bin,img);
					if not resized then
						resized = true;
						Screen.Resize(img:GetWidth(),img:GetHeight());
						Screen.RefreshUI();
					end
					
					Screen.DrawImage(img,0,0);
					Screen.RefreshScreen(false);
				end
				done = true;
		end);		
		
		while not done do
			thread:Sleep(1);
		end
		
		thread:Sleep(sleep_time);
	end
end

co = CoThread.new(1);
co:Start(main_thread);

App.MainLoop();

