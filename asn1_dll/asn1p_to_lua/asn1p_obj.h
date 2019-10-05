#ifndef _C_ASN1P_OBJ_H
#define _C_ASN1P_OBJ_H

#include "cruntime.h"

struct asn1p_obj{
    struct asn1p_obj *_h_next;
    const void *m_obj;
    int m_obj_id;
};

status_t asn1p_obj_init_basic(struct asn1p_obj *self);
status_t asn1p_obj_init(struct asn1p_obj *self);
status_t asn1p_obj_destroy(struct asn1p_obj *self);
status_t asn1p_obj_copy(struct asn1p_obj *self,struct asn1p_obj *_p);
status_t asn1p_obj_comp(struct asn1p_obj *self,struct asn1p_obj *_p);
status_t asn1p_obj_print(struct asn1p_obj *self,int _level);
const void* asn1p_obj_get_obj(struct asn1p_obj *self);
int asn1p_obj_get_obj_id(struct asn1p_obj *self);
status_t asn1p_obj_set_obj(struct asn1p_obj *self,const void *_obj);
status_t asn1p_obj_set_obj_id(struct asn1p_obj *self,int _obj_id);

#endif
