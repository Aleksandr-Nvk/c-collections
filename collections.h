#include <stdlib.h>

/* basic list structure, a wrapping around an array */
typedef struct list_struct {
    void** array; /* inner array */

    size_t count; /* amount of items currently stored in array */
    size_t capacity; /* possible amount of items stored in the array (can be expanded) */
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
        list->array = calloc(list->capacity, 1); /* used calloc to remove garbage values */
    } else if (list->count == list->capacity) {         /* double the size if needed */
        list->capacity *= 2;
        list->array = realloc(list->array, list->capacity);
    }

    (*list).array[list->count++] = item;
}