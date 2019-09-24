--保存路径，为空的话直接打印
save_path="";

--如何把一个字符串转成文件名
function to_file_name(name)
	return to_lower_underline_case(name);
end

--如何生成ifdef的宏定义
function ifdef_name(name)
    return string.format(
        "__%s_H",
        string.upper(to_file_name(name))
    );
end 

--需要的头文件, h文件
function common_includes_h()
    return long_text([[
        #include "cruntime.h"
        #include "mem.h"
        #include "memfile.h"
    ]],8);
end

--需要的头文件, cpp文件
function common_includes_cpp()
    return long_text([[
        #include "syslog.h"
        #include "mem_tool.h"
    ]],8);
end


