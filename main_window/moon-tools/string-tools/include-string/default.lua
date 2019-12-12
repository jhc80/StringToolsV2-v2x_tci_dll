--包含的字符串表--
string_table={
  "int"
};

--大小写敏感--
case_sensitive = true;

--只查找单字--
word_only = false;

--如果为true, 则列表中的每一行表示一个文件
do_in_files = false;

--是否需要这一行的函数
function need_this_line(line)
    local need = 0;
    for _,str in ipairs(string_table) do
        line:Seek(0);
        if line:SearchStr(str,case_sensitive,word_only) >= 0 then
			need = need + 1;
		end
    end
    return need > 0;
end

