一个完整的例子，展示了能够支持的所有类型

class Test:Base{
	int a; //基本类型
	int *ptr; //指针类型
	string str; //字符串类型
	[weak] Obj *weak_ptr; //弱指针类型
	[struct] Stru stru; //声明为struct 类型
	array<int> arr1; //未知大小的数组
	array<int,10> arr2; //固定大小的数组
	int arr_2[1024]; //传统的数组声明方式也支持
	array<Obj> obj_arr; //对象数组
	array<string> str_arr; //字符串数组
	[optional] int opt_val1; //可选项
	[optional] Obj opt_obj1; //对象可选项
	[optional] string opt_str; //可选字符串
	array<int> *ptr_arr; //指针数组这么声明
	array<Obj> *obj_ptr_arr; //对象类型指针数组
}

可以给class加上 [NameSpace ns] 之类的hint来声明名字空间

[NameSpace ns]
class Test{
	ns1::Obj obj; //变量也是可以带命名空间的
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

声明为struct类型，相应的操作都会变成类似于 memcpy的操作
不会对struct进行深拷贝的操作。

可以通过 [Includes hello world] 这样的hint给文件加入自定义的include
头文件

class Test{	
	[noxml] Foo foo;
	[nobson] Bar bar;	
}

可以在前面加上 [noxml] 和 [nobson] 来使生产成的代码没有这两个的成员的 Xml和Bson相关的调用


