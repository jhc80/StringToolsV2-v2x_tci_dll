C_BEGIN_CLOSURE_FUNC(test_func)
{
    C_CLOSURE_PARAM_INT(e,0);
    return OK;
}
C_END_CLOSURE_FUNC(test_func)

struct closure c;
closure_init(&c);
closure_set_func(&c,test_func);
closure_set_param_int(&c,0,123);
########################################
C_BEGIN_CLOSURE_FUNC(test_func)
{
    C_CLOSURE_PARAM_INT(e,0);
    return OK;
}
C_END_CLOSURE_FUNC(test_func)

C_NEW_CLOSURE(pc,test_func);
closure_set_param_int(pc,0,123);
##########################################
C_BEGIN_CLOSURE_FUNC(on_search_dir)
{
    C_CLOSURE_PARAM_INT(e,0);
    if(e == C_EVENT_BEGIN_DIR || e == C_EVENT_SINGLE_FILE)
    {
        C_CLOSURE_PARAM_PTR(char*,file_name,1);
        C_CLOSURE_PARAM_PTR(char*,full_name,2);
        C_CLOSURE_PARAM_INT(is_dir,3);
        C_CLOSURE_PARAM_INT64(size,4);
        C_CLOSURE_PARAM_INT64(last_write_time,5);
    }
    return OK;
}
C_END_CLOSURE_FUNC(on_search_dir)
    
struct closure c;
closure_init(&c);
closure_set_func(&c,on_search_dir);
############################################
C_BEGIN_CLOSURE_FUNC(on_timer)
{
    return OK;
}
C_END_CLOSURE_FUNC(on_timer)

struct task_timer *pt = tasktimer_new(&g_globals.taskmgr,1000,0);
closure_set_func(&pt->callback,on_timer);
############################################
C_BEGIN_CLOSURE_FUNC(on_acceptor_event)
{
    int event,fd,err;
    C89_CLOSURE_PARAM_INT(event,0);

    if(event == C_TASK_TCP_ACCEPTOR_EVENT_NEW_CLIENT)
    {
        C89_CLOSURE_PARAM_INT(fd,1);
        LOG("new client %d",fd);
    }
    else if(event == C_TASK_TCP_ACCEPTOR_EVENT_STOP)
    {
        C89_CLOSURE_PARAM_INT(err,1);
    }
    return OK;
}

struct task_tcp_acceptor *acceptor;
X_MALLOC(acceptor,struct task_tcp_acceptor,1);
tasktcpacceptor_init(acceptor,&mgr);
tasktcpacceptor_set_listen_port(acceptor,8001);
tasktcpacceptor_start(acceptor);
closure_set_func(&acceptor->callback,on_acceptor_event);

#############################################

C_BEGIN_CLOSURE_FUNC(on_simplelinkservice_event)
{
    int event;
    C89_CLOSURE_PARAM_INT(event,0);

    if(event == C_SIMPLE_LINK_SERVICE_EVENT_GOT_MESSAGE)
    {
        LINKRPC_HEADER *header;
        struct mem *header_data,*data;

        C89_CLOSURE_PARAM_PTR(LINKRPC_HEADER*,header,1);
        C89_CLOSURE_PARAM_PTR(struct mem*, header_data,2);
        C89_CLOSURE_PARAM_PTR(struct mem*, data,3);
        
        PS(mem_cstr(header_data));
        PS(mem_cstr(data));
    }

    return OK;
}
C_END_CLOSURE_FUNC(on_simplelinkservice_event)

struct simple_link_service ls;
simplelinkservice_init(&ls,&mgr,0);
simplelinkservice_set_server_name(&ls,"127.0.0.1");
simplelinkservice_set_port(&ls,8001);
simplelinkservice_start(&ls);
closure_set_func(&ls.callback,on_simplelinkservice_event);

