require("common_consts");
require("utils_common");

local _global_ref_table={};
function global_ref(obj)
    table.insert(_global_ref_table,obj);
end


function is_windows()
    return true;
end

--判断是否是空白字符--
function is_white_char(ch)
    return ch == 32 or ch == 9 or ch == 10 or ch == 13;
end

--打印整个文件--
function print_whole_file(filebase)
    App.DumpFile(filebase);
end

--从文件中或者编辑框中load文本，如果文件名不存在或者加载
--失败，就从编辑框中读取代码
function load_from_file_or_editor(in_file)
	
	if not in_file or in_file=="" then
		return App.LoadText();
	else
		local editor = App.LoadText();
		
		local map_file = new_mmapfile(in_file,"r");
		if map_file then 
            --防止局部变量被提前释放，
            --注意内存将被泄漏，直到lua虚拟机被释放
            global_ref(map_file); 
            
			local mem = map_file:Stream();
			mem:SetIsReadOnly(true);
			return mem;
		else			
			return editor;
		end
	end
end

--在文件中进行替换--
function replace_in_file(filebase, src_str,dst_str, case_sensitive, word_only)
    if not dst_str then dst_str = "" end
	local mf_file = new_memfile();
	filebase:Seek(0);
	filebase:ReplaceStr(src_str,dst_str,case_sensitive,word_only,mf_file);
	filebase:SetSize(0);
	filebase:WriteFile(mf_file);
	mf_file:Destroy();
end

--在多个文件中进行批量替换--
function batch_replace_in_files(file_table, rep_table,case_sensitive, word_only)
	for _,file in pairs(file_table) do	
		for _,r in pairs(rep_table) do
			replace_in_file(file,r[1],r[2],case_sensitive,word_only);
		end	
	end
end

function replace_string(str, src_str,dst_str,case_sensitive,word_only)
	local mem = new_memfile();
	mem:Puts(str);
	replace_in_file(mem,src_str,dst_str,case_sensitive,word_only);
	local ret = file_to_string(mem);
	mem:Destroy();
	return ret;
end

--转成大写驼峰是命名，比如 hello_world 会被转成
--HelloWorld
function to_big_camel_case(str)
    local camel = "";
    local big = true;

    for i=1,string.len(str),1 do
        local ch = string.byte(str,i);
        if  ch == CHAR_SPACE  or ch == CHAR_UNDERLINE then
            big = true;
        else
            if big then
                camel = camel..string.upper(string.char(ch));
                big = false;
            else
                camel = camel..string.char(ch);
            end
        end
    end
    return camel;
end

--转成小写驼峰式命名，比如 hello_world 会被转成 helloWorld
function to_small_camel_case(str)
    local big_camel = to_big_camel_case(str);
    local first = string.byte(big_camel,1);
    return string.lower(string.char(first))..string.sub(big_camel,2);
end

--转换成下划线命名，比如 hello world(空格分隔)会被转成
-- hello_world
function to_underline_case(str)
    local tmp = "";
    
    local last_ch = 0;
    for i=1,string.len(str),1 do
        local ch = string.byte(str,i);
        
        if ch == CHAR_SPACE then
            ch = CHAR_UNDERLINE;
        end

        if not (ch == CHAR_UNDERLINE and last_ch == CHAR_UNDERLINE) then            
            tmp = tmp..string.char(ch);
        end
        
        last_ch = ch;
    end
    return tmp;
end

--驼峰式命名转成空格分隔的字符串--
function camel_to_man_case(camel_str)
    local man_str="";
    
    local last_ch = 0;
    
    for i=1,string.len(camel_str),1 do
        local ch = string.byte(camel_str,i);
        
        if     ((last_ch >= CHAR_a and last_ch <=CHAR_z) 
            or (last_ch >= CHAR_0 and last_ch <= CHAR_9))
            and ch >= CHAR_A and ch <= CHAR_Z 
        then
            man_str = man_str.." ";
        end
        
        if not (last_ch == CHAR_SPACE and ch == CHAR_SPACE) then
            man_str = man_str..string.char(ch);        
        end
        
        last_ch = ch;
    end

    return man_str;
end

--驼峰式命名转成下划线风格的命名--
function camel_to_underline_case(camel_str)
    return to_underline_case(camel_to_man_case(camel_str));
end

--驼峰式命名转成下划线风格的命名,小写--
function to_lower_underline_case(str)
    return string.lower(camel_to_underline_case(str));
end

--驼峰式命名转成下划线风格的命名,大写--
function to_upper_underline_case(str)
    return string.upper(camel_to_underline_case(str));
end

--第一个字符变成小写
string.lower_first_char=function(s)
    return string.lower(
        string.char(string.byte(s,1))
    )..string.sub(s,2);
end

--第一个字符变成大写写
string.upper_first_char=function(s)
    return string.upper(
        string.char(string.byte(s,1))
    )..string.sub(s,2);
end



--转换[[]]定义的lua长字符串的换行方式--
function long_text(text,strip)
    local mf = MemFile.new();
    local mf_file = mf:FileBase();
    
    mf_file:Puts(text);
    
    local mem,mem_file = new_mem();
    
    mf_file:Seek(0);
    
    local ret = "";
    
    while mf_file:ReadLine(mem_file) do
        local str = mem:CStr();
        if not strip then
            ret = ret..str..EOL;
        else
            ret = ret..string.sub(str,strip+1)..EOL;
        end
    end
    
    return ret;
end

--把十六进制转换成二进制文件--
function hex_file_to_bin_file(hex_file, bin_file)
    hex_file:Seek(0);    
    local part;
    while not hex_file:IsEnd() do
        local ch = hex_file:Getc();
        local bval = HEX_TO_BIN_TABLE[ch];
        if bval then
            if not part then 
                part = bval*16             
            else 
                bin_file:Putc(part+bval);
                part = nil;
            end
        end
    end
end

--把二进制转成十六进制--
function bin_file_to_hex_file(bin_file,hex_file,line_width)
	bin_file:Seek(0);
	local c = 1;
	while not bin_file:IsEnd() do
		local ch = (bin_file:Getc()&0xff);
		hex_file:Puts(string.format("%02x",ch));
		
		local eol = false;
		if line_width > 0 and c % line_width == 0 then
			hex_file:Puts(EOL);
			eol = true;
		end
		
		if not eol then
			hex_file:Puts(" ");
		end
		
		c = c + 1;
	end
end

--启动一个计时器
function set_timeout(func,interval)
    local timer = Timer.new();
    timer:SetTimeout(interval and interval or 1000);
    timer:SetOneShot(true);
    timer:SetCallback(func); 
    timer:Start();    
    return timer;
end

function maybe_printnl(str)
	if not str then return end
	printnl(str);
end

function _binary(hex_str)
    local tmp_hex = Mem.new();
    tmp_hex:SetRawBuf(hex_str);
    local mem = new_mem(tmp_hex:GetSize()/2);
    hex_file_to_bin_file(tmp_hex,mem);
    return mem;
end

