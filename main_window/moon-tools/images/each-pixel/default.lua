--注意，原图像文件会被覆盖--

--如何转换每一个点，返回处理后的rgba值--
function convert_pixel(x,y, c)
	local r,g,b,a = rgba(c);
	return r,g,b,a;
end
