require("common");
require("utils");
require("peer_tunnel_server");
require("peer_tunnel_client");
require("user");

App.ClearScreen();
App.StartNet();

local clien_table={};

for i,v in ipairs(tunnel_table) do
    local remote_server = v[1];
    local remote_port = v[2];
    local local_listening_port = v[3];

    local client = PeerTunnelClient.new();
    client:InitClientSidePeer(peer_server,peer_port);
    client:SetName(peer_name.."-"..i);
    client:SetDestPeerName(remote_peer_name);
    client:SetRemote(remote_server,remote_port);
    client:Start();        
    client:StartListeningLocalPort(local_listening_port);
    client:StartAutoClearThread();
    printfnl("listening on local port %d -> %d",local_listening_port,remote_port);
    table.insert(clien_table,client);
end

App.MainLoop();

