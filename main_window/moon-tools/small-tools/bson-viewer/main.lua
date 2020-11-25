require("common");
require("bson");
App.ClearScreen();
----------------------------------------------------
require("user");

local bson = Bson.new();

if not bson:LoadBson(bson_file) then
	printfnl("load bson %s fail.",bson_file);
	return
end

print(bson:ToJson());

