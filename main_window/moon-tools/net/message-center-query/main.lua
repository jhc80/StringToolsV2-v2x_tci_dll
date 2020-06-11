require("common")
require("peer_service_base")
require("user")
require("cothread")

App.ClearScreen();

METHOD_MC_GETALLPEERS = 8000001;

MessageCenterClient = class(PeerServiceBase);

function MessageCenterClient:ctor()
end

function MessageCenterClient:OnRequest(_context,_param)
--##Begin OnRequest ##--
    local method = _context.method;
--##End OnRequest ##--
end

--@@Begin Method GetAllPeers @@--
function MessageCenterClient:GetAllPeers(_callback)
    local _cbid = self:AddCallback(_callback);
    return self:SendRequest(nil,METHOD_MC_GETALLPEERS,_cbid);
end
--@@End Method GetAllPeers @@--

--@@Begin Method GetAllPeers_Async @@--
function MessageCenterClient:GetAllPeers_Async(thread)
    local ret = {};
    local done = false;
    
    self:GetAllPeers(function(res,val)
        ret.result = res;
        ret.value = val;
        done = true;
    end);
    
    while not done and not thread:IsDead() do
        thread:Sleep(1);
    end
    
    return ret;
end
--@@End Method GetAllPeers_Async @@--

App.StartNet();

client = MessageCenterClient.new();
client:InitClientSidePeer(server,port);
client:SetName("string-tools-client-temp");
client:SetDestPeerName(query_peer_name);
client:Start();

function main_thread(thread)
	
	while true do
		local done = false;
		printnl("-------------------------");
		client:GetAllPeers(function(ret,val)
			if val and val.RetVal0 then
				print_table(val.RetVal0);
			else
				print("fail.");
			end
			done = true;
		end);
		
		while not done do
			thread:Sleep(100);
		end
		
		if interval == 0 then
			break;
		end
		
		thread:Sleep(interval);
	end
	
	App.QuitMainLoop();
end

if interval > 0  and interval < 1000 then
	interval = 1000;
end

co = CoThread.new();
co:Start(main_thread);

App.MainLoop();
