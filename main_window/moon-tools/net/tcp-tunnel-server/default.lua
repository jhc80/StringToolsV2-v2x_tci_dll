--是否启动自己的messagecenter--
start_message_center = false;

--messager center的ip地址--
peer_server = "api.cv-test.cn";

--messager center的端口号--
peer_port = 23456;

--自己的peer名字--
peer_name = "tcp-tunnel-server-001";

--超时时间 ms,本地连接最大保持时间，如果本地连接超过这个时间不活动--
--就会被强制断开连接, 防止被大量建立不活动连接--
timeout = 60*1000;
