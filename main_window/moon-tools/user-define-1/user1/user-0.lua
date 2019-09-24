App.ClearScreen();

local s = 1;
for i=1,500,1 do
	s = s * 2;
	printf("2^%d = ",i);
	printnl(s);
end