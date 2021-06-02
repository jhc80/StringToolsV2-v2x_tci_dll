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

C语言中还有一种用法，就是先声明一个定长的数组，表示最大长度，然后用一个长度的成员表示
实际使用的数据长度，这种情况也是支持的。比如
class Test{
	int len; //实际使用的长度
	[size=MAX] array<int32_t,_obj.len> arr; 
}
支持的方法就是在前面加上一个[size=XXX]来表示最大数据长度，同时使用变长数组的声明方法。


可以通过 [BasicType XXX int32_t] 添加一个自定义的basic type类型，例如
[BasicType XXX int32_t]
class Test{
	XXX x;
}