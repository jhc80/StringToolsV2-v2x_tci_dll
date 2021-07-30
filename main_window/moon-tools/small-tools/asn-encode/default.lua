--lua数据文件，如果为空则从编辑框读取
lua_in_file = "";

-- 不是所有的asn1格式都支持，只支持以下的消息类型，
-- 如果消息类型选择错误就不能正确地解码
-- 1 - V2X 国标 2017版
-- 2 - V2X 国标 2019版
-- 3 - V2X 国标 2020版
-- 4 - 高新兴 OBU 通讯协议
-- 5 - V2X 国标 2020 Day2 版 
-- 6 - V2X 国标 2020版 安全协议
-- 7 - V2X 一致性测试TCI接口

message_type = 3;

--ASN1描述符的名字
descriptor_name="MessageFrame";

--编码后要保存的二进制文件名，如果为空，则以十六进制的形式保存到编辑框
save_file="";
