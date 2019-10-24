--分隔符--
split_chars=" \t\r\n!@#$%^=&*()|+-\\*/{}[];.\":\',?/<>~";

--提取哪些单词--
which_words={
  1,2,3
};

--从尾部开始--
from_tail = false;

--是否删除--
delete = false;

--如何合并这些单词,对delete模式不起作用--
function how_to_combine(all,line)
	if all[3] ~= "" then
	    printfnl("ret.%s = %s(obj:%s());",all[1],all[3],all[2]);
	else
		printfnl("ret.%s = obj:%s();",all[1],all[2]);
	end
end