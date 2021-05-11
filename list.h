#include <stdlib.h>

#define MIN_CAPACITY 4  /* min capacity an array is expanded to when You add an item to a zero-capacity list */

/* basic list structure, a wrapping around an array */
typedef struct List {
    void** array;

    size_t count;            /* amount of items currently stored in array */
    size_t capacity;            /* possible amount of items stored in the array (can be expanded) */
} List;

/* creates a new list with zero capacity and returns it */
List list_new(void) {
    List new_list = {NULL, 0, 0};
    return new_list;
}

/* returns an item from list by index or NULL if index is out of range */
void* list_of_index(List* list, size_t index) {
    if (index >= list->capacity) {         /* Throw the error if index is out of range */
        perror("INDEX WAS OUT OF RANGE");
        return NULL;
    }

    return list->array[index];
}

/* adds item to list */
void list_add(List* list, void* item) {
    if (list->capacity == 0) {          /* allocate initial 4 bytes if empty */
        list->capacity = MIN_CAPACITY;
        list->array = malloc(list->capacity * sizeof(void*));
    } else if (list->count == list->capacity) {         /* double the size if needed */
        list->capacity *= 2;
        list->array = realloc(list->array, list->capacity * sizeof(void*));
    }

    list->array[list->count++] = item;
}

/* removes the first occurrence of item from list */
void list_remove(List* list, void* item) {
    for (int i = 0; i < list->count; ++i) {
        if (list->array[i] == item) {
            for (int k = i; k < list->count; ++k) {     /* Defragmentation of list */
                list->array[k] = list->array[k + 1];
            }
            --list->count;
            break;
        }
    }
}

/* removes all items from list, keeps capacity unchanged */
void list_clear(List* list) {
    list->count = 0;
}

/* completely deallocates list */
void list_dealloc(List* list) {
    list->count = 0;
    list->capacity = 0;

    free(list->array);
}