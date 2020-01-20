采用命令行模式，模型支持的命令有

ls <path> 
列出文件名

run <cmd>
远程执行命令，客户端并不显示执行结果

cd <dir>
进入远程目录
如果只有cd则显示当前路径
如果路径以/开头则被当成绝对路径

pwd
显示当前远程路径

cls or clear
清除屏幕

get <file>
下载当前路径下的文件或目录。
下载路径则是属性中的 download_path


