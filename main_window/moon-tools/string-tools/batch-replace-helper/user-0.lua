App.ClearScreen();

--自动生成各种case的替换表
local rep_table={
	{"SensorImage","GnssEvent"},
}

for _,v in ipairs(rep_table) do
	add(v[1],v[2]);
	add(string.lower(v[1]),string.lower(v[2]));
	add(string.upper(v[1]),string.upper(v[2]));
	add(to_big_camel_case(v[1]),to_big_camel_case(v[2]));
	add(to_small_camel_case(v[1]),to_small_camel_case(v[2]));
	add(to_lower_underline_case(v[1]),to_lower_underline_case(v[2]));
	add(to_upper_underline_case(v[1]),to_upper_underline_case(v[2]));
end

