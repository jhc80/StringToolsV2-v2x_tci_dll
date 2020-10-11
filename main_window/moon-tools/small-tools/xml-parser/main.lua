require("common")
require("user")

local g_classes = {};

function valid_var_name(name)
	return string.gsub(name,"[^%w]","_");
end

function guess_value_type(value)	
	if not guess_type then
		return "string";
	end
	
	if value=="true" or value=="false" then
		return "bool";
	end
	
	if tonumber(value) then	
		if string.find(value,".",1,true) then
			return "double";
		else
			return "int";
		end	
	end

	return "string";
end

function parse_attributes(node)
	local name = node:GetName();
	if not g_classes[name] then
		g_classes[name]={name=name};
	end
	
	node:RestartAttrib();	
	local key = new_mem();
	local val = new_mem();	
	local cls = g_classes[name];
		
	while node:GetNextAttrib(key,val) do
		if not cls.attributes then
			cls.attributes={};
		end		
		cls.attributes[key:CStr()] = {
			name = key:CStr(),
			value = val:CStr(),
		}
	end
	
	key:Destroy();
	val:Destroy();	
	return cls;
end

function parse_xml(root)	
	local cls = parse_attributes(root);	 
	
	if root:GetStringValue() then	
		cls.has_value = true;	
	end
	
	local children = {};
	local child = root:GetChild();
	while child do
	    parse_xml(child);
		local key = child:GetName();
		if not children[key] then
			children[key] = {
				count=1,
                name=key,
			}
		else
			children[key].count = children[key].count+1;
		end
		child = child:GetNext();
	end
	
	if not cls.children then
		cls.children = children;
	else
		for k,v in pairs(children) do
            if not cls.children[k] then
                cls.children[k] = v;
            elseif v.count > cls.children[k].count then
                cls.children[k] = v;                
            end
		end		
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
	xml:Destroy();
end

if not parse_files then
	local mem_text = App.LoadText();
	App.ClearScreen();
	parse_single_file(mem_text);
else
	local mem_text = App.LoadText();
	App.ClearScreen();
	
	local line = new_mem();
	mem_text:Seek(0);
	
	while mem_text:ReadLine(line) do
		line:Trim();
		local file = new_mem(line:CStr());
		if not file then
			return -1;
		else
			parse_single_file(file);
			file:Destroy();
		end
	end
end

local all_lists={};
    
for _,cls in pairs_ordered(g_classes) do	
	add_code_switches();
	printfnl("class %s {", class_name(cls.name));
	
	if cls.attributes then
		for _,attr in pairs_ordered(cls.attributes) do
            printf("    [name=%s]",attr.name);
			printfnl(" %s %s;", guess_value_type(attr.value), member_name(attr.name));
		end
	end
	
	if cls.children then
		for _,child in pairs_ordered(cls.children) do			
			if child.count == 1 then
                printf("    [name=%s]",child.name);
				printfnl(" %s %s;",class_name(child.name),member_name(child.name));
			else
                printf("    [array,name=%s]",child.name);
				printfnl(" %s %s;",array_class_name(child.name),
                    array_member_name(child.name));
                all_lists[child.name] = child.name;
			end			
		end
	end

	if cls.has_value then	
        print("    [value]");
		printnl(" string value;");	
	end	
	printfnl("}"..EOL);    
end
    
for _,name in pairs_ordered(all_lists) do
	add_code_switches();
    printfnl("[Stack of %s]",class_name(name));
    printfnl("class %s{}",array_class_name(name));
    printnl("");
end



