require("common")
require("user")

local g_xml_table = {};

function parse_single_node(node)
	local path = node:GetPath();
	if not g_xml_table[path] then
		g_xml_table[path] = {};
	end
	
	local item = g_xml_table[path];
	
	node:RestartAttrib();
	local name = new_mem();
	local val = new_mem();
	
	while node:GetNextAttrib(name,val) do
		item[name:CStr()] = val:CStr();
	end
	
	name:Destroy();
	val:Destroy();
end

function parse_xml(root)	
	parse_single_node(root);
	
	local child = root:GetChild();
	while child do
		parse_xml(child);
		child = child:GetNext();
	end
end

function parse_single_file(file)
	if not file then
		return
	end
	
	if file:GetSize() <= 0 then 
		return 
	end	
	
	local xml = Xml.new();

	if not xml:LoadXml(file) then
		printfnl("can not load xml in text editor");
		return
	end
	
	parse_xml(xml:GetRoot());
end

function print_result()
	App.ClearScreen();
	for k,v in pairs_ordered(g_xml_table) do
		
		printnl(k);
		for kk,vv in pairs_ordered(v) do
			printfnl("    %s = \"%s\"",kk,vv);
		end	
	end
end

if not parse_files then
	local mem_text = App.LoadText();
	App.ClearScreen();
	parse_single_file(mem_text);
	print_result();
else
	local mem_text = App.LoadText();
	App.ClearScreen();
	
	local line = new_mem();
	mem_text:Seek(0);
	
	while mem_text:ReadLine(line) do
		line:Trim();
		local file = new_mem(line:CStr());
		if not file then
			printfnl("load file %s fail.",line:CStr());			
		else
			printfnl("parsing file %s...",line:CStr());
			parse_single_file(file);
			printnl("ok");
			file:Destroy();
		end
	end
	print_result();
end



