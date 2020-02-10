require("common");

mem_text = App.LoadText();
App.ClearScreen();

require("user");

local all = mem_text:CStr();
local start = 1;

while true do
	local s,e = string.find(all,pattern,start);
	if not s then break end

	local cap = string.sub(all,s,e);
	printnl(cap);
	start = e+1;
end


