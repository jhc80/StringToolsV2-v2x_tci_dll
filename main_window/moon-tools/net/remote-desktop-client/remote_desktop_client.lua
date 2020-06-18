require("common")
require("peer_service_base")
require("linkrpc_rd_types")

RemoteDesktopClient = class(PeerServiceBase);

function RemoteDesktopClient:ctor()
end

function RemoteDesktopClient:OnRequest(_context,_param)
--##Begin OnRequest ##--
    local method = _context.method;
--##End OnRequest ##--
end

--@@Begin Method TakeScreenShot @@--
function RemoteDesktopClient:TakeScreenShot(_ratiox, _ratioy, _quality, _callback)
    local _cbid = self:AddCallback(_callback);
    local _param={
        ratiox = {_double_=_ratiox},
        ratioy = {_double_=_ratioy},
        quality = {_double_=_quality},
    };
    return self:SendRequest(_param,METHOD_RD_TAKESCREENSHOT,_cbid);
end
--@@End Method TakeScreenShot @@--

--@@Begin Method TakeScreenShot_Async @@--
function RemoteDesktopClient:TakeScreenShot_Async(thread, _ratiox, _ratioy, _quality)
    local ret = {};
    local done = false;
    
    self:TakeScreenShot(_ratiox,_ratioy,_quality,function(res,val)
        ret.result = res;
        ret.value = val;
        done = true;
    end);
    
    while not done and not thread:IsDead() do
        thread:Sleep(1);
    end
    
    return ret;
end
--@@End Method TakeScreenShot_Async @@--

--@@ Insert Method Here @@--
