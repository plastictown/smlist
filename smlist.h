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

/*
* Макрос используется для явного указания компилятору
* наиболее или наименее вероятной ветки в условии if.
* Пример: if(unlikely(a<b)){...} говорит компилятору
* о том, что вероятность выполнения условия маловероятна
*/
#ifdef __GNUC__
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)
#else
#define likely(x)   (x)
#define unlikely(x) (x)
#endif // __GNUC__

/*
* Флаги состояния ноды, можно объединять логическим ИЛИ:
* int flag|=DATA_NULL|NEXT_NULL; и проверять логическим И:
* if(flag & SIZE_NULL){...}
*/
enum NodeState
{
    NODE_NULL=1, // Указатель на структуру равен NULL
    NEXT_NULL=2, // Указатель на следующий элемент (next) равен NULL
    DATA_NULL=4, // Указатель на данные (data) равен NULL
    SIZE_NULL=8  // Размер данных (data_sz) равен нулю
};

struct sm_node
{
    struct sm_node* next;   // следующий элемент
    void*           data;   // данные
    uint16_t        data_sz;// длина данных
};

/** @brief выделяет память под новый элемент, а также
 * память под данные в новом элементе
 * @param data указатель на данные. данные копируются в новый элемент
 * @param data_sz размер данных в байтах
 * @return указатель на выделенную память либо NULL в случае неудачи
 */
NODE* sm_list_alloc_node(const void*, uint16_t);
/**
 * @brief добавляет элемент в конец списка
 * @param
 * @param
 * @return
 *
 */
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
