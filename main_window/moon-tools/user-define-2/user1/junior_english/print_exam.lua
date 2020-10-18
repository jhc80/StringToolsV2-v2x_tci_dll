App.ClearScreen();
require("english_table");

local start = 1;
local count = 50;
local print_english = false;
local print_type = true;
local print_chinese = true;

for i = start, start+count, 1 do
	local v = english_table[i];
	if not v then break end 
	
	printf("%d.  ",i-start+1);
	if print_english then
		printf("%s",v.english);
	else
		printf("                 ");
	end

	if print_type then
		printf("%s ",v.type);	
	end	

	if print_chinese then
		printf("%s",v.chinese);	
	end	

	printnl("");	
end