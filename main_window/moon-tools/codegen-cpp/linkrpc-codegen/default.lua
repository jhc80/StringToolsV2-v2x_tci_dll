--idl源文件，如果为空，则从文本框读取--
idl_source="";

--如果不为空就保存到文件--
save_path = "";

--如何转成c++的类名的方法--
function c_class_name(name)
	return "C"..name;
end

--如何生成service 的函数名字--
function service_func_name(name)
    return "On"..to_big_camel_case(name);
end

--如何生成不是service 的函数名字--
function not_service_func_name(name)
    return to_big_camel_case(name);
end

--如何生成包装参数的类,不带C开头的--
function param_class_name(peer_name,name)
    return "Param_"..
        to_big_camel_case(peer_name)..
        to_big_camel_case(name);
end

--如何生成包装返回值的类,不带C开头的--
function return_class_name(peer_name,name)
    return "RetVal_"..
        to_big_camel_case(peer_name)..
        to_big_camel_case(name);
end

--生成方法ID的名字--
function func_id_name(peer_name,name)
    return string.upper(
        "METHOD_"..peer_name.."_"..name
    );
end

--参数的getter方法名字--
function param_get_func_name(name)
    return "Get"..to_big_camel_case(name);
end

--参数的setter方法名字--
function param_set_func_name(name)
    return "Set"..to_big_camel_case(name);
end
-------------------------------------
--定义基本数据类型的映射表--
-------------------------------------
basic_type_table={
	{"int","%d","Int32"},
	{"int8_t","%d","Int32"},
	{"int16_t","%d","Int32"},
	{"int32_t","%d","Int32"},
	{"int64_t","%lld","Int64"},
    {"fsize_t","%lld","Int64"},
	{"int_ptr_t","%d","Int32"},
	{"intptr_t","%d","Int32"},
	{"char","%d","Int32"},
	{"short","%d","Int32"},
	{"long","%d","Int32"},
	{"uint_t","%d","Int32"},
	{"uint8_t","%d","Int32"},
	{"uint16_t","%d","Int32"},
	{"uint32_t","%d","Int32"},
	{"uint64_t","%lld","Int64"},
	{"uchar","%d","Int32"},
	{"ushort","%d","Int32"},
	{"ulong","%ld","Int32"},
	{"float","%f","Double"},
	{"double","%f","Double"},
	{"bool","%d","Boolean"},
	{"void","%x","Int32"},
    {"status_t","%d","Int32"},
};


--[[ 

一个例子
[Peer test][StartId 10000]
[Client TestClient 20000]
class TestService{
	[service] int Add(int a, int b);
	int Sub(int a, int b);
	[service] void SayHello(string something);	
	[service] array<Good> GetGood();
	[service] (int status, array<uint8_t> data) GetData(int size);
}

]]

