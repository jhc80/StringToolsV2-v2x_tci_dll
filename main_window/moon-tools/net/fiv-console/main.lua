require("common");
require("user");

App.ClearScreen();
App.StartNet();
-------------------------
function monitor_thread(thread)
    local exit_count = 0;    
    while true do
        if g_peer:GetSendingQueueLength() == 0 then
            exit_count = exit_count + 1;
            if exit_count >= 10 then
                printnl("send ok.");
                return App.QuitMainLoop();
            end
        else
            exit_count = 0;
        end
        thread:Sleep(100);
    end
end

g_monitor_thread = nil;
function start_monitor_thread()
    g_monitor_thread = CoThread.new(10);
    g_monitor_thread:Start(monitor_thread,g_monitor_thread);    
end

--------------------------------
g_peer = MessagePeer.new();
g_peer:SetServer(config.server);
g_peer:SetPort(config.port);
g_peer:SetName(config.name);
g_peer:Start();

local command = string.trim(command_or_file);

if FileManager.IsFileExist(command) then
    local mem = new_mem(command);    
    command = mem:CStr();
end

g_peer:SendMessage(
    config.to,
    0x12345678,0,
    BODY_TYPE_STRING|MSG_TYPE_SIGNAL,
    command
);

start_monitor_thread();

App.MainLoop();
