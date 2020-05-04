App.ClearScreen();

require("common")
require("peer_service_base")

METHOD_MC_GETALLPEERNAMES = 8000001;

MessageCenterClient = class(PeerServiceBase);

function MessageCenterClient:ctor()
end

function MessageCenterClient:OnRequest(_context,_param)
--##Begin OnRequest ##--
    local method = _context.method;
--##End OnRequest ##--
end

--@@Begin Method GetAllPeerNames @@--
function MessageCenterClient:GetAllPeerNames(_callback)
    local _cbid = self:AddCallback(_callback);
    return self:SendRequest(null,METHOD_MC_GETALLPEERNAMES,_cbid);
end
--@@End Method GetAllPeerNames @@--

--@@Begin Method GetAllPeerNames_Async @@--
function MessageCenterClient:GetAllPeerNames_Async(thread)
    local ret = {};
    local done = false;
    
    self:GetAllPeerNames(function(res,val)
        ret.result = res;
        ret.value = val;
        done = true;
    end);
    
    while not done and not thread:IsDead() do
        thread:Sleep(1);
    end
    
    return ret;
end
--@@End Method GetAllPeerNames_Async @@--

App.StartNet();

client = MessageCenterClient.new();
client:InitClientSidePeer("111.231.32.67",23456);
client:SetName("test-client");
client:SetDestPeerName("message-center-query-on-tencent-heptane");
client:Start();

client:GetAllPeerNames(function(ret,val)
	print(ret);
	print_table(val);
end);


App.MainLoop();