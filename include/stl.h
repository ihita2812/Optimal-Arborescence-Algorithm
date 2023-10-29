#ifndef STL_H_
#define STL_H_

#include <stdio.h>
#include <stdlib.h>

//LIST

typedef struct list {
    void** items;
    int capacity;
    int size;
} list;
 
void list_init(list*);
int list_size(list*);
static void list_resize(list*, int);
void list_add(list*, void*);
void list_set(list*, int, void*);
void *list_get(list*, int);
int list_max(list*); //only works if list contents are unsigned integers
void list_delete(list*, int);
void list_free(list*);

//STACK

typedef struct stack {
    void** items;
    int capacity;
    int size;
} stack;

void stack_init(stack* s);
static void stack_resize(stack* s, int capacity);
void stack_push(stack* s, void* item);
void* stack_top(stack* s);
void stack_pop(stack* s);
void stack_free(stack* s);

#endif