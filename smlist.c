#include "smlist.h"

void sm_list_sys_error(const char* message)
{
    perror(message);
    exit(errno);
}

int sm_list_node_state(NODE* node)
{
    int state=0;
    if(node==NULL) {state|=NODE_NULL; return state;}
    if(node->data==NULL) state|=DATA_NULL;
    if(node->data_sz==0) state|=SIZE_NULL;
    if(node->next==NULL) state|=NEXT_NULL;
    return state;
}

int sm_list_push_back(NODE* head, NODE* node)
{
    if(sm_list_empty(node)) return -1;

    if(unlikely(sm_list_empty(head)))
    {
        head->data=calloc(1,node->data_sz);
        memcpy(head->data, node->data, node->data_sz);
        head->data_sz=node->data_sz;
        head->next=NULL;
        free(node->data);
        free(node);
        return 0; //OK
    }
    else // at least one element
    {
        // check sizes
        if(head->data_sz!=node->data_sz) return -1; // other datatype

        NODE* tail=sm_list_get_tail(head);
        if(tail==NULL) return -1;
        tail->next=sm_list_alloc_node(node->data, node->data_sz);
        tail=tail->next;
        free(node->data);
        free(node);
        return 0;
    }
    return -1; //NOK
}

NODE* sm_list_alloc_node(const void* data, uint16_t data_sz)
{
    NODE* pNode=(NODE*)calloc(1,sizeof(NODE)); if(pNode==NULL) return NULL;
    pNode->next=NULL;
    pNode->data_sz=data_sz;
    pNode->data=(NODE*)calloc(1,data_sz); if(pNode->data==NULL) {free(pNode); pNode=NULL; return NULL;}
    memcpy(pNode->data, data, data_sz);
    return pNode;
}

int sm_list_empty(const NODE* head)
{
    if(head==NULL) return 1;
    if(head->data_sz==0 || head->data==NULL) return 1;
    return 0;
}

NODE* sm_list_get_tail(NODE* head)
{
    if(sm_list_empty(head)) return NULL;
    NODE* tail=head;
    while(tail->next)tail=tail->next;
    return tail;
}

int sm_list_remove_tail(NODE* head)
{
    if(sm_list_empty(head)) return -1;
    if(sm_list_get_size(head)==1){free(head->data); head->data=NULL; head->next=NULL; return 0;}

    NODE* tail=head;
    NODE* prev=head;

    while(tail->next)
    {
        prev=tail;
        tail=tail->next;
    }
    free(tail->data);
    free(tail);
    prev->next=NULL;
    return 0;
}

uint32_t sm_list_get_size(NODE* head)
{
    if(sm_list_empty(head)) return 0;
    NODE* tail=head;
    uint32_t counter=1;
    while(tail->next)
    {
        ++counter;
        tail=tail->next;
    }
    return counter;
}

NODE* sm_list_find(NODE* node, const void* data)
{
    if(sm_list_empty(node)) return NULL;

    NODE* pNode=node;
    while(pNode->next)
    {
        if(!memcmp(pNode->data, data, node->data_sz)) return pNode;
        pNode=pNode->next;
    }
    return NULL;
}

int sm_list_pop_back(NODE* head, void* dest)
{
    if(sm_list_empty(head)) return -1;

    NODE* tail=sm_list_get_tail(head);
    if(tail==NULL) return -1;
    memcpy(dest,tail->data,tail->data_sz);
    return sm_list_remove_tail(head);
}

int sm_list_push_front(NODE* head, NODE* node)
{
    if(sm_list_empty(node)) return -1;

    if(unlikely(sm_list_empty(head)))
    {
        head->data=calloc(1,node->data_sz);
        memcpy(head->data, node->data, node->data_sz);
        head->data_sz=node->data_sz;
        head->next=NULL;
        free(node->data);
        free(node);
        return 0; //OK
    }
    else // at least one element
    {
        // check sizes
        if(head->data_sz!=node->data_sz) return -1; // other datatype

        NODE* tmp=sm_list_alloc_node(head->data, head->data_sz);
        if(tmp==NULL) return -1;
        tmp->next=head->next;

        memcpy(head->data, node->data, head->data_sz);
        head->next=tmp;

        free(node->data);
        free(node);

        return 0;
    }
    return -1; //NOK
}

int sm_list_remove_front(NODE* head)
{
    if(unlikely(sm_list_empty(head))) return -1;
    NODE* tmp=head->next;
    if(tmp==NULL)
    {
        free(head->data);
        head->data=NULL;
        head->next=NULL;
        head->data_sz=0;
        return 0;
    }
    memcpy(head->data, tmp->data, tmp->data_sz);
    head->next=tmp->next;

    free(tmp->data);
    free(tmp);

    return 0;
}

int sm_list_get_front(NODE* head, void* dest)
{
    if(sm_list_empty(head)) return -1;
    if(dest==NULL) return -1;
    memcpy(dest, head->data, head->data_sz);
    return 0;
}

int sm_list_pop_front(NODE* head, void* dest)
{
    if(sm_list_get_front(head,dest)==-1) return -1;
    return sm_list_remove_front(head);
}

void sm_list_clear(NODE* head)
{
    if(sm_list_empty(head)) return;
    while(head->next) sm_list_remove_front(head);
    free(head->data);
    head->data=NULL;
}

