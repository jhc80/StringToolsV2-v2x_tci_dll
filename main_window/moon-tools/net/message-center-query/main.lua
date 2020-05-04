require("common");
require("peer_service_base")
require("user");
App.ClearScreen();

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
client:InitClientSidePeer(server,port);
client:SetName("string-tools-client-temp");
client:SetDestPeerName(query_peer_name);
client:Start();

client:GetAllPeerNames(function(ret,val)
	if val and val.RetVal0 then
		print_table(val.RetVal0);
	else
		print("fail.");
	end
end);


App.MainLoop();