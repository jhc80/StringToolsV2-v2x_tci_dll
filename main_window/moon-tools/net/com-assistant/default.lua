--串口号--
com_name = "COM1";

--模特率--
baud_rate=115200;

--数据位--
data_bits = 8;

--停止位--
stop_bits = 1;

--奇偶校验--
parity = "n";

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
