App.ClearScreen();

local i = 0;
for_each_line(mem_text_file,function(line)
	local str = line:CStr();
	i = i + 1;
	
printfnl("LUA_IS_VALID_USER_DATA_FUNC(C%s,%s)",str,string.lower(str));
printfnl("LUA_GET_OBJ_FROM_USER_DATA_FUNC(C%s,%s)",str,string.lower(str));
printfnl("LUA_NEW_USER_DATA_FUNC(C%s,%s,%s)",str,string.lower(str),string.upper(str));
printfnl("LUA_GC_FUNC(C%s,%s)",str,string.lower(str));
printfnl("LUA_IS_SAME_FUNC(C%s,%s)",str,string.lower(str));
printfnl("LUA_TO_STRING_FUNC(C%s,%s)",str,string.lower(str));
printnl("");

printfnl("bool is_%s(lua_State *L, int idx)",string.lower(str));
printfnl("{        ");
printfnl("    const char* ud_names[] = {");
printfnl("        LUA_USERDATA_%s,",string.upper(str));
printfnl("    };            ");
printfnl("    lua_userdata *ud = NULL;");
printfnl("    for(size_t i = 0; i < sizeof(ud_names)/sizeof(ud_names[0]); i++)");
printfnl("    {");
printfnl("        ud = (lua_userdata*)luaL_testudata(L, idx, ud_names[i]);");
printfnl("        if(ud)break;");
printfnl("    }");
printfnl("    return %s_is_userdata_valid(ud);  ",string.lower(str));
printfnl("}");

printnl("");
printfnl("    {\"__gc\",%s_gc_},",string.lower(str));
printfnl("    {\"__tostring\",%s_tostring_},",string.lower(str));
printfnl("    {\"__is_same\",%s_issame_},",string.lower(str));
printfnl("    {\"new\",%s_new},",string.lower(str));


end);
