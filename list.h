#include <stdlib.h>

/* basic list structure, a wrapping around an array */
typedef struct list {
    void** array;           /* inner array */

    size_t count;            /* amount of items currently stored in array */
    size_t capacity;            /* possible amount of items stored in the array (can be expanded) */
} list;

/* creates a new list with zero capacity and returns it */
list new_list(void) {
    list new_list = {NULL, 0, 0};
    return new_list;
}

/* returns an item from list by index or NULL if index is out of range */
void* index_of_list(list* list, size_t index) {
    if (index >= list->capacity) {         /* Throw the error if index is out of range */
        perror("INDEX WAS OUT OF RANGE");
        return NULL;
    }

    return list->array[index];
}

/* adds item to list */
void add_to_list(list* list, void* item) {
    if (list->capacity == 0) {          /* allocate initial 4 bytes if empty */
        list->capacity = 4;
        list->array = calloc(list->capacity, 1);            /* used calloc to remove garbage values */
    } else if (list->count == list->capacity) {         /* double the size if needed */
        list->capacity *= 2;
        list->array = realloc(list->array, list->capacity);
    }

    list->array[list->count++] = item;
}

/* removes the first occurrence of item from list */
void rem_fr_list(list* list, void* item) {
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

/* removes all items from list, keeps capacity */
void rem_all_fr_list(list* list) {
    for (int i = 0; i < list->count; ++i) {
        list->array[i] = NULL;
    }
    list->count = 0;
}

/* removes all items from list, sets capacity to 0 */
void clear_list(list* list) {
    list->count = 0;
    list->capacity = 0;

    free(list->array);
}