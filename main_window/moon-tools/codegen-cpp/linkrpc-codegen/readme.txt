举一个例子， Client和Server端的函数是一一对应的。加上[service]前缀说明要生成OnXXXX的函数，
同时在另一侧生成对应的函数 [Peer]设定的是名字空间

[Peer test][StartId 10000]
[Client TestClient 20000]
class TestService{
	[service] int Add(int a, int b);
	int Sub(int a, int b);
	[service] void SayHello(string something);	
	[service] array<Good> GetGood();
	[service] (int status, array<uint8_t> data) GetData(int size);
}
