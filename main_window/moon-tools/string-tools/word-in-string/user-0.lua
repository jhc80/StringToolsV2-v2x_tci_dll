--分隔符--
split_chars=" \t\r\n!@#$%^=&*()|+-\\*/{}[];.\":\',?/<>~";

--提取哪些单词--
which_words={
  4,7
};

--从尾部开始--
from_tail = false;

--是否删除--
delete = false;

--如何合并这些单词,对delete模式不起作用--
function how_to_combine(all,line)
    printfnl("\"%s\",\"%s\"},",all[1],all[2]);
end