//一个例子
class Header{ 
	[string] array<uint8_t,8>  ID;
	uint8_t  LayerID;
	uint16_t CMDType;
	uint16_t CMD;
	uint16_t  DataLen;
	array<uint8_t,_obj.DataLen> Data;
	[binary] array<char,100> mydata;
}

生成 lua和c结构体互转的代码。
对于 array有 [string] 和 [binary] 两种hint
可以暗示是把这个 array当成字符串还是二进制来处理。
可以把 array的大小指定成 _obj.xxx 的形式，可以从某种程度上实现变长数组的处理。

