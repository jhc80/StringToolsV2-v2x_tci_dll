C++到java的绑定，下面列出支持的各种数据类型

class Hello{
	void Hello();  //无参构造函数
	void Hello(int a); //有参构造函数
	int GetA();  //返回整型
	status_t SetA(int a); //参数中带有整数
	status_t SetStr(string str); //参数中带有字符串
	string GetStrStr(); //返回字符串类型
	
    array<int> GetIntArr(); //返回基本数据类型的数组
    status_t SetIntArr(array<int> _int_arr); //参数中带有基本数据类型的数组    
    status_t SetStrArr(array<string> _str_arr); //参数中带有字符串数组
    array<string> GetStrArr(); //返回字符串数组
	
	status_t SetGood(array<Good> gg); //参数中带有对象数组
	array<Good> GetGood(); //返回值是对象数组
	
	[callback] int add(int a, int b); //回调函数声明
	void SetCallback([callback] onadd); //生成设置回调函数的方法
}

回调函数也支持各种参数类型，和返回值类型，包括各种数组。
但是目前的回调函数生成的代码不能生成调用 static方法的代码，
回调函数只能用于回调某对象的成员方法，对于static成员的回调需要用户自己实现。
还有，由于对用户如何处理回调函数返回值的方法无法知晓，因此这部分的代码可能是
不正确的。对于回调函数的处理，代码生成器只能保证大部分的代码正确，对于如何处理
返回值则需要用户自己检查。


