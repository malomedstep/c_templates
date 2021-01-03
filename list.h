#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>
#include <assert.h>
#include <memory.h>

#define DeclareList(Type)                                                                                        \
typedef struct _##Type##List {                                                                                   \
    Type* at;                                                                                                    \
    size_t _capacity;                                                                                            \
    size_t len;                                                                                                  \
} Type##List;                                                                                                    \
                                                                                                                 \
void Type##List_add(Type##List *list, Type value) {                                                              \
    assert(list != NULL);                                                                                        \
                                                                                                                 \
    if (list->len == list->_capacity) {                                                                          \
        list->_capacity = list->_capacity == 0 ? 4 : list->_capacity * 2;                                        \
        Type *temp_items = malloc(list->_capacity * sizeof(Type));                                               \
        if (list->len > 0) {                                                                                     \
            memcpy_s(temp_items, list->len * sizeof(Type), list->at, list->len * sizeof(Type));                  \
        }                                                                                                        \
        free(list->at);                                                                                          \
        list->at = temp_items;                                                                                   \
    }                                                                                                            \
    list->at[list->len] = value;                                                                                 \
    list->len++;                                                                                                 \
}                                                                                                                \
                                                                                                                 \
Type##List* Type##List_create() {                                                                                \
    Type##List *list = malloc(sizeof(Type##List));                                                               \
    list->_capacity = 0;                                                                                         \
    list->len = 0;                                                                                               \
    list->at = NULL;                                                                                             \
    return list;                                                                                                 \
}                                                                                                                \
                                                                                                                 \
void Type##List_destroy(Type##List **ptr) {                                                                      \
    assert(ptr != NULL);                                                                                         \
    assert(*ptr != NULL);                                                                                        \
                                                                                                                 \
    free((*ptr)->at);                                                                                            \
    free(*ptr);                                                                                                  \
    *ptr = NULL;                                                                                                 \
}                                                                                                                \
                                                                                                                 \
void Type##List_remove(Type##List *list, size_t position)  {                                                     \
    assert(position >= 0 && position <= list->len);                                                              \
                                                                                                                 \
    for(size_t i = position; i < list->len - 1; i++) {                                                           \
        list->at[i] = list->at[i + 1];                                                                           \
    }                                                                                                            \
    list->len--;                                                                                                 \
}                                                                                                                \
                                                                                                                 \
void Type##List_insert(Type##List *list, Type value, size_t position) {                                          \
    assert(list != NULL);                                                                                        \
    assert(position <= list->len);                                                                               \
                                                                                                                 \
    if (position == list->len) {                                                                                 \
        Type##List_add(list, value);                                                                             \
    } else {                                                                                                     \
        if (list->len == list->_capacity) {                                                                      \
            Type *temp = malloc((list->len+1) * sizeof(Type));                                                   \
            list->_capacity *= 2;                                                                                \
            for(size_t i = 0; i < position; i++) {                                                               \
                temp[i] = list->at[i];                                                                           \
            }                                                                                                    \
            for(size_t i = position; i < list->len; i++) {                                                       \
                temp[i + 1] = list->at[i];                                                                       \
            }                                                                                                    \
            free(list->at);                                                                                      \
            list->at = temp;                                                                                     \
        } else {                                                                                                 \
            for(size_t i = list->len; i > position; i--){                                                        \
                list->at[i] = list->at[i - 1];                                                                   \
            }                                                                                                    \
        }                                                                                                        \
        list->at[position] = value;                                                                              \
        list->len++;                                                                                             \
    }                                                                                                            \
}                                                                                                                \
                                                                                                                 \

#define foreach(list, func)                                                                                      \
    for(size_t i = 0; i < list->len; i++) {                                                                      \
        func(list->at + i);                                                                                      \
    }


#define List_var(Name, Type) Type##List* Name = Type##List_create()


#define add(List, Value)                                                                                         \
    _Generic((List),                                                                                             \
        struct _intList*:    intList_add,                                                                        \
        struct _doubleList*: doubleList_add)                                                                     \
    (List, Value)

#define insert(List, Value, Position)                                                                            \
    _Generic((List),                                                                                             \
        struct _intList*:    intList_insert,                                                                     \
        struct _doubleList*: doubleList_insert)                                                                  \
    (List, Value, Position)

#define remove(List, Position)                                                                                   \
    _Generic((List),                                                                                             \
        struct _intList*:    intList_remove,                                                                     \
        struct _doubleList*: doubleList_remove)                                                                  \
    (List, Position)

#define destroy(List)                                                                                            \
    _Generic((List),                                                                                             \
        struct _intList*:    intList_destroy,                                                                    \
        struct _doubleList*: doubleList_destroy)                                                                 \
    (&List)

#endif // _LIST_H_