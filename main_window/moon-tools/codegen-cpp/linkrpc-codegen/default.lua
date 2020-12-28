--idl源文件，如果为空，则从文本框读取--
idl_source="";

--如果不为空就保存到文件--
save_path = "";

--生成java代码的package name--
function java_package_name(name)
	return "com.linkrpc."..string.lower(name);
end

--如何转成c++的类名的方法--
function c_class_name(name)
	return "C"..name;
end

--如何转成Java的类名的方法--
function java_class_name(name)
	return to_big_camel_case(name);
end

--如何生成service 的函数名字--
function service_func_name(name)
    return "On"..to_big_camel_case(name);
end

--如何生成不是service 的函数名字--
function not_service_func_name(name,is_async)
    local name = to_big_camel_case(name);
	if is_async then
		name = name.."_Async";
	end
	return name;
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

--java client和service类通用import的packages--
function java_common_import_packages()
return [[
import android.util.Log;
import com.cvtest.common.RpcServiceBase;
import com.cvtest.common.RpcParamBase;
import com.cvtest.common.RpcCallContext;        
import com.cvtest.common.RpcCallback;
import com.cvtest.common.Callback;
import com.jni.common.CMiniBson;
]]
end

-------------------------------------
--定义基本数据类型的映射表--
-------------------------------------
basic_type_table={
	{"int","%d","Int32","int"},
	{"int8_t","%d","Int32","byte"},
	{"int16_t","%d","Int32","short"},
	{"int32_t","%d","Int32","int"},
	{"int64_t","%lld","Int64","long"},
    {"fsize_t","%lld","Int64","long"},
	{"int_ptr_t","%d","Int32","long"},
	{"intptr_t","%d","Int32","long"},
	{"char","%d","Int32","byte"},
	{"short","%d","Int32","short"},
	{"long","%d","Int32","int"},
	{"uint_t","%d","Int32","int"},
	{"uint8_t","%d","Int32","byte"},
	{"uint16_t","%d","Int32","short"},
	{"uint32_t","%d","Int32","int"},
	{"uint64_t","%lld","Int64","long"},
	{"uchar","%d","Int32","byte"},
	{"ushort","%d","Int32","short"},
	{"ulong","%ld","Int32","int"},
	{"float","%f","Double","float"},
	{"double","%f","Double","double"},
	{"bool","%d","Boolean","boolean"},
	{"void","%x","Int32","void"},
    {"status_t","%d","Int32","boolean"},
};

