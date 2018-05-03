#ifndef SMLIST_H_INCLUDED
#define SMLIST_H_INCLUDED

#include <stdint.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define NODE struct sm_node
#define SUCCESS 0
#define FAIL -1

#ifdef __GNUC__
#define likely(x)       __builtin_expect(!!(x),1)
#define unlikely(x)     __builtin_expect(!!(x),0)
#else
#define likely(x)   (x)
#define unlikely(x) (x)
#endif // __GNUC__

/*
* flags using:
* int flag|=DATA_NULL|NEXT_NULL;
* if(flag & SIZE_NULL){...}
*/
enum NodeState
{
    NODE_NULL=1, // NULL pointer
    NEXT_NULL=2, // next pointer is NULL
    DATA_NULL=4, // data pointer is NULL
    SIZE_NULL=8  // zero data size
};

struct sm_node
{
    struct sm_node* next;   // next element
    void*           data;   // data
    uint16_t        data_sz;// data len in bytes
};

NODE* sm_list_alloc_node(const void*, uint16_t);
int sm_list_push_back(NODE*, NODE*);
int sm_list_node_state(NODE*);
int sm_list_empty(const NODE*);
NODE* sm_list_get_tail(NODE*);
int sm_list_remove_tail(NODE*);
uint32_t sm_list_get_size(NODE*);
NODE* sm_list_find(NODE*, const void*);
int sm_list_pop_back(NODE*, void*);
int sm_list_push_front(NODE*, NODE*);
int sm_list_remove_front(NODE*);
int sm_list_pop_front(NODE*, void*);
int sm_list_get_front(NODE*, void*);
void sm_list_clear(NODE*);

#endif // SMLIST_H_INCLUDED
