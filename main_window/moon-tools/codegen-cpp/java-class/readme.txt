一个完整的例子，展示了能够支持的所有类型

[CodeSwitch code_mark=true,bson=true]

class Test:Base{
	int a; //基本类型
	string str; //字符串类型
	array<int> arr1; //未知大小的数组
	array<int,10> arr2; //固定大小的数组
	int arr_2[1024]; //传统的数组声明方式也支持
	array<Obj> obj_arr; //对象数组
	array<string> str_arr; //字符串数组
}

可以直接通过hint使用一些选项开关，例如

[CodeSwitch bson=true,weak_ref=true,code_mark=true]
class Test{
}

可以通过 [BasicType XXX int32_t] 添加一个自定义的basic type类型，例如
[BasicType XXX int32_t]
class Test{
	XXX x;
}

控制是否生成 setter和 getter的方法是在属性前面加上 [noset] 或 [noget],
如果不加则默认生成 setter和getter方法，例如

class Test{	
	[noset] int a; //不会生成set方法
	[noget] int b; //不会生成get方法
	[noget,noset] int c; //既不生成get方法，也不生成set 方法
}


