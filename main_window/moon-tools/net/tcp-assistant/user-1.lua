--是否作为tcp服务器--
as_tcp_server = true;
--服务器的监听端口--
listen_port = 3000;

--远程服务器的名字或ip--
server = "127.0.0.1"
--要连接的服务器的端口号--
port = 3000;

--发送完成后自动清空--
clear_after_send = false;

--是否使用十六进制--
use_hex = false;

--接收到数据打印之前的回调函数--
function after_recv_msg(mem)
end

--用户线程，可以在这里做一些自己的事情--
--send_message(mem)函数可以用来发送原始数据--
function user_thread(thread)
end