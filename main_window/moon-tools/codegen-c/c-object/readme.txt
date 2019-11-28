可以支持 C语言的虚函数了，使用的方法是声明 virtual类型的函数
destroy和get_this_pointer是两个保留的虚函数，
需要保持声明不变。
继承的话，如果父类带virtual的函数，则需要写成下面这样

下面的例子

class Test{
	int a;
	
	[virtual] status_t destroy();
	[virtual] void* get_this_pointer();
	[virtual] int Add(int a, int b);
}

class Good:virtual Test{
	string name;
}




