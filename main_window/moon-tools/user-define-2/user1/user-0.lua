App.ClearScreen();

for_each_line(mem_text_file,function(line)
	local str = line:CStr();
    printfnl("status_t hw_m2m_%s_to_comm(hw_m2m_%s_t *hw, struct comm_%s *comm)",str,str,str);
end);
