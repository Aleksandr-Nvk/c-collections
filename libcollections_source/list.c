#include <stdlib.h>
#include <stdio.h>

#define MIN_CAPACITY 4  /* default capacity of an empty list when you add the first item to it */

/* basic list structure, a wrapping around an array */
typedef struct List {
    void** array;

    size_t count;            /* amount of items currently stored in list */
    size_t capacity;            /* possible amount of items stored in list (can be expanded) */
} List;

/* returns a new blank list */
List list_new(void) {
    List new_list = {NULL, 0, 0};
    return new_list;
}

/* returns an item from a list by an index (or NULL if the index is out of range) */
void* list_of_index(List* list, size_t index) {
    if (index < list->count || index >= 0) {
        return list->array[index];
    }

    /* Throw the following error if the index is out of range */
    perror("\nINDEX WAS OUT OF RANGE");
    return NULL;
}

/* adds an item to a list */
void list_add(List* list, void* item) {
    if (list->capacity == 0) {
        list->capacity = MIN_CAPACITY;          /* set default capacity if list is empty */
        list->array = malloc(list->capacity * sizeof(void*));
    } else if (list->count == list->capacity) {
        list->capacity *= 2;            /* double capacity of list if more space is needed */
        list->array = realloc(list->array, list->capacity * sizeof(void*));
    }

    list->array[list->count++] = item;
}

/* removes the first occurrence of given item from a list */
void list_remove(List* list, void* item) {
    for (int i = 0; i < list->count; ++i) {
        if (list->array[i] == item) {
            /* Defragmentation of the list */
            for (int k = i; k < list->count - 1; ++k) {
                list->array[k] = list->array[k + 1];
            }
            --list->count;
            break;
        }
    }
}

/* removes all items from a list (capacity is unchanged) */
void list_clear(List* list) {
    list->count = 0;
}

/* completely deallocates a list */
void list_dealloc(List* list) {
    list->count = 0;
    list->capacity = 0;

    free(list->array);
}