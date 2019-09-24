App.ClearScreen();

--------------先生成单词表--------
local random = true;

local danci_table={};

local i = 0;
local tmp = {};

for_each_line(mem_text_file,function(line)
	line:Trim();
	if line:StrLen() == 0 then
		return
	end
	
	local str = line:CStr();
    if i % 2 == 0 then
		tmp.english = str;
	else
		tmp.chinese = str;		
		table.insert(danci_table,tmp);
		tmp = {};
	end

	i = i + 1;
end);
---------------------------------------------
function print_space(len)
	for i=1,len,1 do
		print(" ");
	end
end
--------------------打印---------------------
local print_english = false;
local print_chinese = true;

local max_space = 100;
local left_space = max_space;


function print_word(v)
	local total_length = string.len(v.english)*2 + string.len(v.chinese);
	
	if left_space < total_length then
		left_space = max_space;
		printnl("");
	end
	
	if print_chinese then
		printf("%s",v.chinese);
	end

	if print_english then
		printf("%s",v.english);	
		print_space(string.len(v.english));
	else
		print_space(string.len(v.english)*2);
	end

	left_space = left_space - total_length;	
end

if not random then
	for k,v in ipairs(danci_table) do	
		print_word(v);
	end
else
	
	local rand_tab = {};
	for k,v in ipairs(danci_table) do	
		rand_tab[v.english] = v;
	end

	for k,v in pairs(rand_tab) do
		print_word(v);		
	end

end
