#include "../include/stl.h"

//LIST
// note: add sort() funcion in optimised way

void list_init(list* v) {
    v->capacity = 4;
    v->size = 0;
    v->items = malloc(sizeof(void*) * 4);
    if (v->items == NULL) {printf("Malloc failure\nCODE: 17\n"); exit(17);}
}

int list_size(list* v) {
    return v->size;
}

static void list_resize(list* v, int capacity) { 
    void** items = realloc(v->items, sizeof(void*) * capacity);
    if (items == NULL) {printf("Realloc failure\nCODE: 18\n"); exit(18);}
    if (items) {
        v->items = items;
        v->capacity = capacity;
    } else {
        printf("resize failed\n");
    }
}

void list_add(list* v, void* item) {
    if (v->capacity == v->size) {
        list_resize(v, v->capacity * 2);
    }
    *(v->items+(v->size++)) = item;
}

void list_set(list *v, int index, void *item) {
    if (index >= 0 && index < v->size)
        v->items[index] = item;
}

void* list_get(list* v, int index) {
    if (index >= 0 && index < v->size) {
        return v->items[index];
    }
    else {
        return NULL;
    }
}

//only works if list contents are unsigned integers
int list_max(list* l) {
    int max_index = 0;

    for (int i=1; i<l->size; i++) {
        if (*(unsigned int*)list_get(l, i) > *(unsigned int*)list_get(l, max_index))
        max_index = i;
    }

    return max_index;
}

void list_delete(list *v, int index) {
    if (index < 0 || index >= v->size)
        return;
 
    v->items[index] = NULL;
    int i;
    for (i = index; i < v->size - 1; i++) {
        v->items[i] = v->items[i + 1];
        v->items[i + 1] = NULL;
    }
 
    v->size--;
 
    if (v->size > 0 && v->size == v->capacity / 4)
        list_resize(v, v->capacity / 2);
}

void list_free(list *v) {
    free(v->items);
}

//STACK

void stack_init(stack* s) {
    s->capacity = 4;
    s->size = 0;
    s->items = malloc(sizeof(void*) * 4);
    if (s->items == NULL) {printf("Malloc failure\nCODE: 19\n"); exit(19);}
}

static void stack_resize(stack* s, int capacity) { 
    void** items = realloc(s->items, sizeof(void *) * capacity);
    if (items == NULL) {printf("Realloc failure\nCODE: 20\n"); exit(20);}
    if (items) {
        s->items = items;
        s->capacity = capacity;
    }
}

void stack_push(stack* s, void* item) {
    if (s->capacity == s->size)
        stack_resize(s, s->capacity * 2);
    s->items[s->size++] = item;
}

void* stack_top(stack* s) {
    return s->items[s->size-1];
}

void stack_pop(stack* s) {
    s->items[s->size-1] = NULL;
    s->size--;
 
    if (s->size > 0 && s->size == s->capacity / 4)
        stack_resize(s, s->capacity / 2);
}

void stack_free(stack* s) {
    free(s->items);
}
