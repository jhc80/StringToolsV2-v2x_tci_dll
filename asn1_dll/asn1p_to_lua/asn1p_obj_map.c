#include "asn1p_obj_map.h"
#include "syslog.h"
#include "mem_tool.h"

static uint32_t bob_32bit_integer_hash(uint32_t a);

bool_t asn1p_obj_map_equals(struct asn1p_obj_map *self,struct asn1p_obj *node1, struct asn1p_obj *node2);
struct asn1p_obj* asn1p_obj_map_clone_node(struct asn1p_obj_map *self,struct asn1p_obj *node);
status_t asn1p_obj_map_del_node(struct asn1p_obj_map *self,struct asn1p_obj *node);

status_t asn1p_obj_map_init_basic(struct asn1p_obj_map *self)
{
	self->m_capacity = 0;
	self->m_data = 0;
	self->m_size = 0;
	return OK;
}
status_t asn1p_obj_map_init(struct asn1p_obj_map *self,int capacity)
{
	asn1p_obj_map_init_basic(self);
	self->m_capacity = capacity;
	MALLOC(self->m_data,struct asn1p_obj*,capacity);
	memset(self->m_data,0,capacity*sizeof(struct asn1p_obj*));
	return OK;
}
status_t asn1p_obj_map_destroy(struct asn1p_obj_map *self)
{
	int i;
	struct asn1p_obj *q,*p;
	
	if(self == NULL)return ERROR;

	if(self->m_data == NULL)
		return OK;

	for(i = 0; i < self->m_capacity; i++)
	{
		p  = self->m_data[i];
		while(p)
		{
			q = p->_h_next;
			asn1p_obj_map_del_node(self,p);
			p = q;			
		}			
	}
	FREE(self->m_data);
	asn1p_obj_map_init_basic(self);
	return OK;
}

status_t asn1p_obj_map_put_ptr(struct asn1p_obj_map *self,struct asn1p_obj *ptr)
{
	int code;
	struct asn1p_obj *p;

	ASSERT(ptr);

	if(asn1p_obj_map_get(self,ptr) != NULL)
		return ERROR;

	code = asn1p_obj_map_hash_code(self,ptr);
	ASSERT(code >= 0 && code < self->m_capacity);
	p = self->m_data[code];
	if (p == NULL)
	{
		self->m_data[code] = ptr;
		ptr->_h_next = NULL;
	}
	else
	{
		while(p->_h_next)
		{
			p = p->_h_next;
		}
		p->_h_next = ptr;
		ptr->_h_next = NULL;
	}
	self->m_size++;
	return OK;
}

status_t asn1p_obj_map_put(struct asn1p_obj_map *self,struct asn1p_obj *hashentry)
{
	struct asn1p_obj *tmp = asn1p_obj_map_clone_node(self,hashentry);
	if(!asn1p_obj_map_put_ptr(self,tmp))
	{
		asn1p_obj_map_del_node(self,tmp);
		return ERROR;
	}
	return OK;
}

struct asn1p_obj* asn1p_obj_map_get(struct asn1p_obj_map *self,struct asn1p_obj *key)
{
	int code;
	struct asn1p_obj *p;

	ASSERT(key);

	code = asn1p_obj_map_hash_code(self,key);
	ASSERT(code >= 0 && code < self->m_capacity);
	p = self->m_data[code];
	while(p)
	{
		if(asn1p_obj_map_equals(self,p,key))
			return p;
		p = p->_h_next;
	}
	return NULL;
}

struct asn1p_obj* asn1p_obj_map_remove(struct asn1p_obj_map *self,struct asn1p_obj *key)
{
	int code;
	struct asn1p_obj *pre,*p;

	ASSERT(key);
	code = asn1p_obj_map_hash_code(self,key);
	if(code < 0 || code >= self->m_capacity)
		return NULL;
	p = self->m_data[code];
	if(p == NULL) return NULL;

	if(asn1p_obj_map_equals(self,p,key))
	{
		self->m_data[code] = p->_h_next;
		self->m_size --;
		return p;
	}
	else
	{
		while(p)
		{
			pre = p;
			p = p->_h_next;
			if(p&&asn1p_obj_map_equals(self,p,key))
			{
				pre->_h_next = p->_h_next;
				self->m_size --;
				return p;
			}
		}
	}

	return NULL;
}
status_t asn1p_obj_map_del(struct asn1p_obj_map *self,struct asn1p_obj *key)
{
	struct asn1p_obj *p = asn1p_obj_map_remove(self,key);
	if(p != NULL)
	{
		return asn1p_obj_map_del_node(self,p);
	}
	return ERROR;
}
int asn1p_obj_map_get_size(struct asn1p_obj_map *self)
{
	return self->m_size;
}
bool_t asn1p_obj_map_is_empty(struct asn1p_obj_map *self)
{
	return asn1p_obj_map_get_size(self) <= 0;
}
status_t asn1p_obj_map_print(struct asn1p_obj_map *self,int _level)
{
	int i;
	int collision = 0;
	int maxLength = 0;

	for(i = 0; i < self->m_capacity; i++)
	{
		struct asn1p_obj *p = self->m_data[i];
		if(p != NULL)
		{
			int len = 0;
			collision--;
			while(p)
			{				
				p = p->_h_next;
				len ++;
				collision++;
			}
			if(len > maxLength)
				maxLength = len;
		}
	}

	return OK;
}
/////////////////////////////////////////////////////////////////////////////////
//Bob Jenkins' 32 bit integer hash function
uint32_t bob_32bit_integer_hash(uint32_t a)
{
	a = (a+0x7ed55d16) + (a<<12);
	a = (a^0xc761c23c) ^ (a>>19);
	a = (a+0x165667b1) + (a<<5);
	a = (a+0xd3a2646c) ^ (a<<9);
	a = (a+0xfd7046c5) + (a<<3);
	a = (a^0xb55a4f09) ^ (a>>16); 
	return a;
}
/////////////////////////////////////////////////////////////////////////////////
int asn1p_obj_map_hash_code(struct asn1p_obj_map *self,struct asn1p_obj *node)
{
	ASSERT(node);
	ASSERT(asn1p_obj_get_obj(node));

	const void *p = asn1p_obj_get_obj(node);
	uint32_t val = (uint32_t)((intptr_t)p);

	return bob_32bit_integer_hash(val) % self->m_capacity;
}
bool_t asn1p_obj_map_equals(struct asn1p_obj_map *self,struct asn1p_obj *node1, struct asn1p_obj *node2)
{
	ASSERT(node1 && node2);
	return asn1p_obj_comp(node1,node2) == 0;
}

struct asn1p_obj* asn1p_obj_map_clone_node(struct asn1p_obj_map *self,struct asn1p_obj *node)
{
	struct asn1p_obj *ptr;
	MALLOC(ptr,struct asn1p_obj,1);
	asn1p_obj_init(ptr);
	asn1p_obj_copy(ptr,node);
	return ptr;
}

status_t asn1p_obj_map_del_node(struct asn1p_obj_map *self,struct asn1p_obj *node)
{
	asn1p_obj_destroy(node);
	FREE(node);
	return OK;
}


