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
