App.ClearScreen();

local i = 0;
local new_tab={};
local exit_tab={};

for_each_line(mem_text_file,function(line)
	local str = line:CStr();
	i = i + 1;

	for v in string.gmatch(str,"%[New Thread (.-)%]") do
		new_tab[v] = 1;
	end

	for v in string.gmatch(str,"%[Thread (.-) exited%]") do
		exit_tab[v] = 1;
	end

end);

for k,_ in pairs(new_tab) do
	if not exit_tab[k] then
		printfnl("thread %s not exit.",k);
	end
end