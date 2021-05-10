require("common");
require("utils");
require("peer_tunnel_server");
require("peer_tunnel_client");
require("user");

App.ClearScreen();
App.StartNet();

server = PeerTunnelServer.new();
if start_message_center then
	App.StartMessageCenter(peer_port,true);
	printfnl("start message center on port %d",peer_port);
	server:InitServerSidePeer();
else
	server:InitClientSidePeer(peer_server,peer_port);
end

server:SetName(peer_name);
server:Start();
server:StartAutoClearThread();
server:SetTimeout(timeout);

App.MainLoop(1);
