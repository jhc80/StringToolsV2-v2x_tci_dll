App.StartMessageCenter(2086);

local server = HelloService.new();
server:InitServerSidePeer();
server:SetName("server-lua");
server:SetDestPeerName("client-lua");
server:Start();

###################################
local client = HelloClient.new();
client:InitClientSidePeer();
client:SetName("client-lua");
client:SetDestPeerName("server-lua");
client:Start();
###################################
function main_thread(thread)
end

local co = CoThread.new();
co:Start(main_thread);

App.MainLoop();
