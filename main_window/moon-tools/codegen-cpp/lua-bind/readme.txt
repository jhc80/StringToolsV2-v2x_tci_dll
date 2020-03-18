lua的绑定支持继承，可以用[SubClass]来声明父类被哪些子类继承，可以声明多个

[SubClass Test]
class Base{
	void Base(); //构造方法，会生成new函数
    [static] void SayHello(string hello); //静态函数的声明
	int Foo(int a); //普通函数的声明
	[callback] void OnGetResult(int p1, string p2); //回调函数的声明
	int Sum(array<int> elems); //参数可以是数组的类型，但不支持对象类型， 返回值也不支持数组类型
}

子类继承父类的声明方法
class Test:Base{
    void Test();
    int Add(int a, int b);    
}
