--asn1 lua 表文件--
--如果为空则从编辑框中读取--
lua_asn1_file="";

--生成文件保存的路径--
--如果为空则仅仅打印--
save_path="";

--实现对名字冲突的修正，比如 long 这个
--名字就和c语言的关键字有冲突
function fix_asn1_member_name(m)
    if m.Identifier == "long" then
        m.Identifier = "Long";
    end
end
