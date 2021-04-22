--messager center的ip地址--
peer_server = "api.cv-test.cn";
--messager center的端口号--
peer_port = 23456;
--远端的peer名字--
remote_peer_name = "tcp-tunnel-server-001";

--自己的peer名字前缀--
peer_name = "tcp-tunnel-client-001";

--远程要连接的目标ip地址--
--远程要连接的目标端口号--
--要映射到本地的哪个端口上--
tunnel_table={
    {"127.0.0.1",22,2222},
};


