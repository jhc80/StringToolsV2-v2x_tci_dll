--字符串模式提取的函数--
--以每一行为单位--
function how_to_extract(line)
	local pattern=".-%((.+)%).+";
	for w in string.gmatch(line,pattern) do
		printnl(w);
	end
end

