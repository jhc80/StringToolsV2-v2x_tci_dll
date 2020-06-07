require("common");
require("user");
require("common");
require("utils");
require("peer_service_base");

METHOD_WC_GETALLPEERS = 8000001;

MessageCenterServer = class(PeerServiceBase);

function MessageCenterServer:ctor()
end

function MessageCenterServer:OnRequest(_context,_param)
--##Begin OnRequest ##--
    local method = _context.method;
    if method == METHOD_WC_GETALLPEERS then
        self:OnGetAllPeer(_context,_param);
    end
--##End OnRequest ##--
end

--@@Begin Method OnGetAllPeerNames @@--
function MessageCenterServer:OnGetAllPeer(_context,_param)
    local peers = App.GetAllPeers();    
    local ret = {};
    if peers then 
        for _,p in ipairs(peers) do
            table.insert(ret,{
                name = p:GetName(),
                sending_queue = p:GetSendingQueueLength(),
            });
        end
    end
    local _ret={
        RetVal0 = ret,
    };
    self:SendReturnValue(_context,_ret);
end
--@@End Method OnGetAllPeerNames @@--

App.ClearScreen();
App.StartNet();

App.StartMessageCenter(port,trust_mode);

App.Sleep(100);
printnl("start message center on port "..port);
printnl("trust mode is ",trust_mode);

g_server = MessageCenterServer.new();
g_server:InitServerSidePeer();
g_server:SetName("message-center-query");
g_server:Start();

App.MainLoop();
