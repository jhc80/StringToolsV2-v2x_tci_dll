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
