一个例子：

test_closure就是closure的名字
前面可以通过 index的 hint来指定索引值
数组的话一定要有大小，会被当成Malloc的参数

class test_closure{
	[index=10] CGlobals *self;
	[index=11] int a;
	[index=12] string name;
	[index=13] array<int,N> arr;
	[index=14] [weak] Object *WeakPtr;
	[index=15] char *ch;
	[index=16] float ff;
}
