require("common");
require("user");

App.ClearScreen();

App.StartNet();

printnl("start message center on port "..port);
printnl("trust mode is ",trust_mode);

App.StartMessageCenter(port,trust_mode);

App.MainLoop();
