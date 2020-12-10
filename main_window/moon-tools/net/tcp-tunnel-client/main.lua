require("common");
require("utils");
require("peer_tunnel_server");
require("peer_tunnel_client");
require("user");

App.ClearScreen();
App.StartNet();

client = PeerTunnelClient.new();
client:InitClientSidePeer(peer_server,peer_port);
client:SetName(peer_name);
client:SetDestPeerName(remote_peer_name);
client:SetRemote(remote_server,remote_port);
client:Start();        
client:StartListeningLocalPort(local_listening_port);
client:StartAutoClearThread();
printfnl("listening on local port %d",local_listening_port);

App.MainLoop();
