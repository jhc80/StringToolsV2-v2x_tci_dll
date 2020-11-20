package_name="com.cvtest.jni";

--idl源文件，如果为空，则从文本框读取--
idl_source="";

--如果不为空就保存到文件--
save_path = "";
------------------------------
--如何把一个字符串转成文件名
function to_file_name(name)
	return to_lower_underline_case(name);
end

--如何转成c++的类名的方法--
function c_class_name(name)
	return "C"..name;
end

--如何生成java的函数名称--
function java_function_name(name)
	return to_small_camel_case(name);
end
-------------------------------------
--定义基本数据类型的映射表--
-------------------------------------
basic_type_table={
{"int","jint"},	
{"int32_t","jint"},
{"uint32_t","jint"},
{"int64_t","jlong"},
{"uint64_t","jlong"},
{"fsize_t","jlong"},
{"uint8_t","jbyte"},
{"byte","jbyte"},
{"int8_t","jbyte"},
{"char","jbyte"},
{"int16_t","jshort"},	
{"uint16_t","jshort"},	
{"short","jshort"},
{"string","jstring"},
{"float","jfloat"},
{"double","jdouble"},
{"void","void"},
{"bool","jboolean"},
{"status_t","jboolean"},	
{"BOOL","jboolean"},	
{"wchar_t","jchar"},
};

--JNI类型映射表--
jni_type_table={
{"jfloat","float","F","FloatArray","jfloatArray"},
{"jdouble","double","D","DoubleArray","jdoubleArray"},
{"jint","int","I","IntArray","jintArray"},
{"jlong","long","L","LongArray","jlongArray"},
{"jstring","String","Ljava/lang/String;","","jobjectArray"},
{"jboolean","boolean","Z","BooleanArray","jbooleanArray"},
{"jshort","short","S","ShortArray","jshortArray"},
{"jbyte","byte","B","ByteArray","jbyteArray"},
{"void","void","V","",""},
{"jchar","char","C","CharArray","jcharArray"},
};
