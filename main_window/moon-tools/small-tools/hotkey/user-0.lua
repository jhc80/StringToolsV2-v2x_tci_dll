function hot_key_func_1()
    run_command("Z:\\v2x\\sources\\JiangHuai\\sources\\webpage\\pack_all.bat");
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
