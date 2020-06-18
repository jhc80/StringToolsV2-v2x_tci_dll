require("common")
require("peer_service_base")
require("linkrpc_rd_types")

RemoteDesktopServer = class(PeerServiceBase);

function RemoteDesktopServer:ctor()
end

function RemoteDesktopServer:OnRequest(_context,_param)
--##Begin OnRequest ##--
    local method = _context.method;
    if method == METHOD_RD_TAKESCREENSHOT then
        self:OnTakeScreenShot(_context,_param);
    end
--##End OnRequest ##--
end

--@@Begin Method OnTakeScreenShot @@--
function RemoteDesktopServer:OnTakeScreenShot(_context,_param)
	take_screen_shot(_param.ratiox,_param.ratioy,_param.quality);
    local _ret={
       jpeg = {_binary_ = jpeg_file},
    };	
    self:SendReturnValue(_context,_ret);
end
--@@End Method OnTakeScreenShot @@--

--@@ Insert Method Here @@--
