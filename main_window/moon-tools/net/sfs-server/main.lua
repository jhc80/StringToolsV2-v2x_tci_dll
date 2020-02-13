require("common");
require("user");
require("bson");
require("win32");
require("simple_file_server")

App.ClearScreen();
App.StartNet();

root_path = FileManager.ToAbsPath(root_path).."\\";

if not FileManager.IsDirExist(root_path) then
	printfnl("root path %s is not exist.",root_path);
	return
end

FileManager.ChangeDir(root_path);
printfnl("root path is %s",FileManager.GetCurDir());
printfnl("start message center on port %d",listen_port);
App.WaitBuffer();
App.StartMessageCenter(listen_port,true);

file_server = SimpleFileServer.new();
file_server:InitServerSidePeer();
file_server:SetName(peer_name);
file_server:SetRootDir(root_path);
file_server:Start();

App.MainLoop();

