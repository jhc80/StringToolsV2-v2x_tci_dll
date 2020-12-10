require("common");
require("utils");
require("http_proxy_server")
require("user");

App.ClearScreen();
App.StartNet();

server = HttpProxyServer.new();
server:StartListening(port);
server:StartAutoClear();

App.MainLoop();
