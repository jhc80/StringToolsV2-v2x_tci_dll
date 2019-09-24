require("common");

App.ClearScreen();
----------------------------------------------------
require("user");

for i=32,126,2 do
	print(string.format(
		"%s -> %d(0x%x)",
		string.char(i),i,i
	));
	
	print("\t");
	
	printnl(string.format(
		"%s -> %d(0x%x)",
		string.char(i+1),i+1,i+1
	));
	
end
