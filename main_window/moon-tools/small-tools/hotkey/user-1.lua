function hot_key_func_1()
	FileManager.ChangeDir("D:\\mydisk\\Program\\VC6\\Projects\\StringToolsV2");
    run_command("start cmd.exe");
end

function hot_key_func_2()
    printnl("hot key func 2");
end
-----------------------------
hotkey_table={
{
    {VK_CONTROL,VK_F1},
    hot_key_func_1
}
,
{
    {VK_CONTROL,VK_F2},
    hot_key_func_2
}
}
