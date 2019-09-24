--源文件夹，可以多个--
from_folders = {
"z:\\tmp\\gen",
};

--要合并的目标文件夹，可以多个--
to_folders = {
"z:\\tmp\\user"
};

--是否在合并完成后删除源文件--
delete_source_file = false;

--[[
代码的自动合并，同名的文件将会根据规则自动完成合并
基本的规则是：
    1. 标记在/*##Begin XXX ##*/和 /*##End XXX ##*/
    之间的代码会被替换，其余的地方保持不变
    
    2. 标记在/*@@Begin XXX YYY @@*/和 /*@@End XXX YYY @@*/
    之间的代码会先按照名字 YYY 进行查找，如果不存在则进行追加    
--]]
