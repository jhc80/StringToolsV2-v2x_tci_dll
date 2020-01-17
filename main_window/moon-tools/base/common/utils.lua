require("common_consts");

local _global_ref_table={};

function global_ref(obj)
    table.insert(_global_ref_table,obj);
end

--按字母顺序排列的pair函数--
function pairs_ordered(tab)
    local order_tab={};
    for k,v in pairs(tab) do
        local tmp = {key=k,val=v};
        table.insert(order_tab,tmp);
    end

    table.sort(order_tab,function(e1,e2)
        if type(e1.key) == "number" and type(e2.key) == number then
            return e1.key < e2.key;
        end
        return string.lower(e1.key) < string.lower(e2.key);
    end);

    local i = 0;
    
    function iter()       
        i = i + 1;
        
        if not order_tab[i] then
            return nil;
        end
        
        return order_tab[i].key,order_tab[i].val;
    end
    
    return iter;
end

--创建mem类的函数,可以传入大小和文件名--
--也可以不写参数，创建默认大小的mem类--
function new_mem(size)
    local mem = Mem.new();
    
    if not size then
        size = LBUF_SIZE;
    end
    
    if type(size) == "number" then
        mem:Malloc(size);
    end
        
    local mem_file = mem:FileBase();
    
    if type(size) == "string" then
        local filename = size;
        if not mem_file:LoadFile(filename) then
            printnl("load file "..filename.." fail");
            return nil;
        end
    end

    return mem,mem_file;
end

--创建memfile类的函数,可以传入大小和文件名--
--也可以不写参数，创建默认大小的memfile类--
function new_memfile(block_size, max_blocks)
    
    local mf = MemFile.new();
    
    if not block_size then
        mf:Init();
    end
    
    if type(block_size) == "number" then
        mf:Init(block_size,max_blocks);
    end
        
    local mf_file = mf:FileBase();
    
    if type(block_size) == "string" then
        local filename = block_size;
        if not mf_file:LoadFile(filename) then
            printnl("load file "..filename.." fail");
            return nil;
        end
    end
    
    return mf,mf_file;    
end

--创建File类的帮助函数--
function new_file(filename,mode)
    if not mode then mode = "rb" end
    
    local file = File.new();
    
    if mode == "r" or mode == "rb" then
        file:SetBufSize(4096*1024);        
    end
    
    if not file:OpenFile(filename,mode) then
        printnl("open file "..filename.." error.");
        return
    end
    
    return file, file:FileBase();    
end

function new_file_no_buffer(filename,mode)
    if not mode then mode = "rb" end
    
    local file = File.new();

    if not file:OpenFile(filename,mode) then
        print("open file "..filename.." error.");
        return
    end
    
    return file;
end

--创建mmapfile的方法，不能创建超过4G的文件，因为-
--是32位程序
function new_mmapfile(filename,mode)
    if not mode then mode = "r" end
    
    local mapfile = MMapFile.new();
    local success;
    
    if mode == "r" then
        success = mapfile:OpenReadOnly(filename);
    end
    
    if not success then
        printnl("map file "..filename.." fail");
        return;
    end
    
    return mapfile,mapfile:Stream();
end

--移除文件名的前缀--
--比如 C:\1.txt ,如果把前缀C:移除，就变成了 \1.txt 了 
function remove_path_prefix(full_name,prefix)    
    if string.find(full_name,prefix,1,true) ~= 1 then
        return
    end
    
    local len = string.len(prefix);
    if len == 0 then return full_name end
    local rpath = string.sub(full_name,len+1);
    return rpath;
end

--分隔文件后缀的列表，逗号分隔， e.g. "c,cpp,h,lua,js"
--返回一个hash表
function split_file_exts_list(exts)
    local tab = {};
    local flag = false;
    
    for k in string.gmatch(exts, "([%a%d]+)") do
        tab[k] = true;
        flag = true;
    end
    
    if flag then
        return tab;
    end
end

--对FileBase类中每一行进行迭代的函数--
function for_each_line(filebase,callback)
    filebase:Seek(0);
    local mem,mem_file = new_mem();
    while filebase:ReadLine(mem_file) do
        if callback(mem,mem_file) then
			break;
		end
    end
end   

--执行一个命令行，并且返回结果--
function execute_command(cmd)
    local f = io.popen(cmd);
    local str = f:read("*a");
    f:close();
    return str;
end

--得到当前的git 的 branch 值--
function git_current_branch(folder)
    local cd = FileManager.GetCurDir();
    local git_folder = FileManager.ToAbsPath(folder);
    FileManager.ChangeDir(git_folder);
    local str = execute_command("git branch");
    FileManager.ChangeDir(cd);
    return string.match(str,"%*%s*([%w_]+)");
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
	local _,mf_file = new_memfile();
	filebase:Seek(0);
	filebase:ReplaceStr(src_str,dst_str,case_sensitive,word_only,mf_file);
	filebase:SetSize(0);
	filebase:WriteFile(mf_file);
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

--去掉字符串前后的空格--
string.trim=function(s)
  return (s:gsub("^%s*(.-)%s*$", "%1"))
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

--打印函数,printf--
function printf(...)
    print(string.format(...));
end

--打印函数，printf最后加上换行符--
function printfnl(...)
    printnl(string.format(...));
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

--把一个filebase类转换成string--
function file_to_string(file)
    local mem, mem_file = new_mem(file:GetSize());
    mem_file:WriteFile(file);    
    return mem:CStr();
end

--把一个filebase类转换成mem--
function file_to_mem(file)
    local mem = new_mem(file:GetSize());
    mem:WriteFile(file);    
    return mem;
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

--启动一个计时器
function set_timeout(func,interval)
    local timer = Timer.new();
    timer:SetTimeout(interval and interval or 1000);
    timer:SetOneShot(true);
    timer:SetCallback(func); 
    timer:Start();    
    return timer;
end
