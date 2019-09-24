#ifndef __C_ASN1P_OBJ_MAP_H
#define __C_ASN1P_OBJ_MAP_H

#include "cruntime.h"
#include "asn1p_obj.h"

struct asn1p_obj_map{
	struct asn1p_obj **m_data;
	int m_capacity;
	int m_size;
};

status_t asn1p_obj_map_init_basic(struct asn1p_obj_map *self);
status_t asn1p_obj_map_init(struct asn1p_obj_map *self,int capacity);
status_t asn1p_obj_map_destroy(struct asn1p_obj_map *self);
status_t asn1p_obj_map_put_ptr(struct asn1p_obj_map *self,struct asn1p_obj *ptr);
status_t asn1p_obj_map_put(struct asn1p_obj_map *self,struct asn1p_obj *hashentry);
struct asn1p_obj* asn1p_obj_map_get(struct asn1p_obj_map *self,struct asn1p_obj *key);
struct asn1p_obj* asn1p_obj_map_remove(struct asn1p_obj_map *self,struct asn1p_obj *key);
status_t asn1p_obj_map_del(struct asn1p_obj_map *self,struct asn1p_obj *key);
int asn1p_obj_map_get_size(struct asn1p_obj_map *self);
bool_t asn1p_obj_map_is_empty(struct asn1p_obj_map *self);
status_t asn1p_obj_map_print(struct asn1p_obj_map *self,int _level);
int asn1p_obj_map_hash_code(struct asn1p_obj_map *self,struct asn1p_obj *node);


#endif

