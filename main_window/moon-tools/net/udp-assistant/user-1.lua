--本地监听端口--
local_port = 30002;

--远程发送的ip和端口号--
remote_ip = "127.0.0.1";
remote_port = 30001;

--发送完成后自动清空--
clear_after_send = false;

--是否使用十六进制--
use_hex = true;

--发送数据之前的回调,可以用来更改原有的内容--
function before_send_msg(mem)
end

--接收到数据打印之前的回调函数--
function after_recv_msg(mem)
end

--用户线程，可以在这里做一些自己的事情--
function user_thread(thread)

end