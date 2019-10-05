#include "asn1p_obj.h"
#include "syslog.h"
#include "mem_tool.h"

status_t asn1p_obj_init_basic(struct asn1p_obj *self)
{
    self->_h_next = NULL;
    self->m_obj = NULL;
    self->m_obj_id = 0;
    return OK;
}

status_t asn1p_obj_init(struct asn1p_obj *self)
{
    asn1p_obj_init_basic(self);
    return OK;
}

status_t asn1p_obj_destroy(struct asn1p_obj *self)
{
    asn1p_obj_init_basic(self);
    return OK;
}

status_t asn1p_obj_copy(struct asn1p_obj *self,struct asn1p_obj *_p)
{
    ASSERT(_p);
    if(self == _p)return OK;

    self->m_obj = _p->m_obj;
    self->m_obj_id = _p->m_obj_id;
    return OK;
}

status_t asn1p_obj_comp(struct asn1p_obj *self,struct asn1p_obj *_p)
{
    ASSERT(_p);
    if(self == _p)return 0;
    return (intptr_t)(self->m_obj - _p->m_obj);
}

status_t asn1p_obj_print(struct asn1p_obj *self,int _level)
{
    return OK;
}

const void* asn1p_obj_get_obj(struct asn1p_obj *self)
{
    return self->m_obj;
}

int asn1p_obj_get_obj_id(struct asn1p_obj *self)
{
    return self->m_obj_id;
}

status_t asn1p_obj_set_obj(struct asn1p_obj *self,const void *_obj)
{
    self->m_obj = _obj;
    return OK;
}

status_t asn1p_obj_set_obj_id(struct asn1p_obj *self,int _obj_id)
{
    self->m_obj_id = _obj_id;
    return OK;
}

