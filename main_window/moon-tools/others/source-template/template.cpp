BEGIN_CLOSURE(on_search_dir)
{
    CLOSURE_PARAM_INT(event,0);
    CLOSURE_PARAM_PTR(char*,file_name,1);
    CLOSURE_PARAM_PTR(char*,full_name,2);
    CLOSURE_PARAM_INT(is_dir,3);
    CLOSURE_PARAM_INT64(size,4);
    CLOSURE_PARAM_INT64(last_write_time,5);
    
    return OK;
}
END_CLOSURE(on_search_dir);

CDirMgr::SearchDir(dir,true,&on_search_dir);
####################################################
BEGIN_CLOSURE_FUNC(on_timeout)
{
    CLOSURE_PARAM_PTR(CObject*,self,10);
    return OK;
}
END_CLOSURE_FUNC(on_timeout);

CTaskTimer *timer = CTaskTimer::NewTimer(GetTaskMgr(),1000,false);
timer->Callback()->SetFunc(on_timeout);
timer->Callback()->SetParamPointer(10,this);
m_AutoTimeoutTimer = timer->GetId();
####################################################
BEGIN_NEW_CLOSURE(on_main_thread)
{
    ASSERT(ON_MAIN_THREAD());
    return OK;
}
END_NEW_CLOSURE(on_main_thread);

POST_TASK_TO_MAIN_THREAD(on_main_thread,0);    
###################################################
BEGIN_CLOSURE(on_enum)
{
    CLOSURE_PARAM_PTR(CCallback*,cb,0);
    CLOSURE_PARAM_PTR(CObject*,self,10);
    return OK;
}
END_CLOSURE(on_enum);

on_enum.SetParamPointer(10,this);
this->EnumAll(&on_enum);
####################################################
status_t CGlobals::StartWebServer()
{
    BEGIN_CLOSURE_FUNC(on_new_client)
    {
        CLOSURE_PARAM_INT(event,0);

        if(event == CTaskTcpAcceptor::EVENT_STOP)
        {
            LOGE("tcp acceptor stopped");
        }

        if(event == CTaskTcpAcceptor::EVENT_NEW_CLIENT)
        {
            CLOSURE_PARAM_INT(socket_fd,1);            
            GLOBAL_WEB_SERVER(ws);
            if(ws->IsConnected())
            {
                LOGW("close a connected web socket");
                ws->Destroy();
                ws->Init(&g_globals.m_TaskMgr);
            }
            LOG("new websocket client %d",socket_fd);
            ws->OnNewClientArrive(socket_fd,true);          
        }
        return OK;
    }
    END_CLOSURE_FUNC(on_new_client);

	ASSERT(!m_TaskMgr.IsTask(m_TaskTcpAcceptor));
	
	int port = 2019;
	
    CTaskTcpAcceptor *acceptor;
    NEW(acceptor, CTaskTcpAcceptor);
	acceptor->Init(&m_TaskMgr);
	acceptor->SetListenPort(port);
	acceptor->Start();
	acceptor->Callback()->SetFunc(on_new_client);
	m_TaskTcpAcceptor = acceptor->GetId();
	
    LOGI("start websocket server on port %d",port);
    return OK;
}
##################################################
BEGIN_MINI_TASK(recv_task)
{
	CTaskNProxy *self = NULL;
	status_t Run(uint32_t interval)
	{
		return OK;
	}
}
END_MINI_TASK(recv_task);

recv_task->Init(GetTaskMgr());
recv_task->self = this;
recv_task->Start(1);    
m_RecvMiniTask = recv_task->GetId();
###################################################

static status_t on_tcp_connector_event(CClosure *closure)
{
    CLOSURE_PARAM_INT(event,0);
    CLOSURE_PARAM_PTR(CTaskVetalkProxy*,self,10);
    ASSERT(self);

    if(event == CTaskTcpConnector::EVENT_STOP)
    {
        CLOSURE_PARAM_INT(err,1);
        if(err != CTaskTcpConnector::ERROR_NONE)
        {            
			self->Restart(CTaskVetalkProxy::ERROR_CONNECT_FAIL);
        }
    }
    else if(event == CTaskTcpConnector::EVENT_CONNECTED)
    {
        CLOSURE_PARAM_PTR(CTcpClient*,client,2);
        ASSERT(client); 
		g_globals.AddHandleToEpoll(client->GetSocketFd());
		self->m_Socket.TransferSocketFd(client);		
    }
    return OK;
}

status_t CTaskVetalkProxy::StartTaskConnector()
{
    ASSERT(!IsTask(m_TaskTcpConnectror));

	m_SocketRwer.Callback()->SetFunc(on_socketrwer_event);
	m_SocketRwer.Callback()->SetParamPointer(10,this);

	GLOBAL_SETTINGS(settings);

    CTaskTcpConnector *pc;
    NEW(pc,CTaskTcpConnector);
    pc->Init(this->GetTaskMgr());
    pc->SetServerName(settings->GetJsonProxyIpAddrStr());
    pc->SetPort(settings->GetJsonProxyPort());
    pc->Callback()->SetFunc(on_tcp_connector_event);
    pc->Callback()->SetParamPointer(10,this);
    pc->Start();

	LOGI("start connecting to json server %s:%d",
		settings->GetJsonProxyIpAddrStr(),
		settings->GetJsonProxyPort()
	);
    m_TaskTcpConnectror = pc->GetId();
    return OK;
}
#####################################################
static status_t on_socketrwer_event(CClosure *closure)
{
    CLOSURE_PARAM_INT(event,0);
    if(event == CSocketReaderWriter::EVENT_ERROR)
    {
        CLOSURE_PARAM_PTR(const char*,err_str,2);
        CLOSURE_PARAM_PTR(CTaskLinkRpc*,self,10);
        ASSERT(self);
        XLOG(LOG_MODULE_MESSAGEPEER,LOG_LEVEL_ERROR,
            "CTaskLinkRpc(%d) socket error: %s",self->GetId(),err_str
        );
        self->Retry(CTaskLinkRpc::ERROR_SOCKET_ERROR);
        self->OnSocketError();
    }
    return OK;
}

CClosure *callback = this->mSocketRwer->Callback();
callback->SetFunc(on_socketrwer_event);
callback->SetParamPointer(10,this);

