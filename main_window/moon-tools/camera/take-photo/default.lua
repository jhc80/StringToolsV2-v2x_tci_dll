--激活哪一个设备--
active_device = 0;

--缩放比例--
scale_x = 1;
scale_y = 1;


--怎样生成照片的名字--
function get_photo_file_name(index)
	return string.format(
		"z:\\tmp\\photo-%04d.jpg",index
	);
end

