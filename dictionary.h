#include <stdlib.h>

#define MIN_CAPACITY 4  /* min capacity an array is expanded to when You add an item to a zero-capacity list */

typedef struct KeyValuePair {
    void* key;
    void* value;
} KeyValuePair;

typedef struct Dictionary {
    KeyValuePair** array;           /* array of 10 arrays, basic structure of hash table */
    void*** keys;

    size_t* counts;         /* stores 10 counts of each nested array */
    size_t* capacities;         /* stores 10 capacities of each nested array */

    size_t count;            /* amount of key-value pairs currently stored in array */
} Dictionary;

Dictionary dict_new() {
    Dictionary new_dictionary = {malloc(10 * sizeof(KeyValuePair*)),
                                 calloc(10, sizeof(void**)),
                                 calloc(10, sizeof(size_t)),
                                 calloc(10, sizeof(size_t)), 0};

    return new_dictionary;
}

/* binds value to key and adds it to dictionary */
void dict_add(Dictionary* dictionary, void* key, void* value) {
    size_t index = (long)key % 10;

    if (dictionary->capacities[index] == 0) {
        dictionary->capacities[index] = MIN_CAPACITY;
        dictionary->array[index] = malloc(dictionary->capacities[index] * sizeof(KeyValuePair));
        dictionary->keys[index] = malloc(dictionary->capacities[index] * sizeof(void*));
    } else if (dictionary->capacities[index] == dictionary->counts[index]) {
        dictionary->capacities[index] *= 2;
        dictionary->array[index] = realloc(dictionary->array[index], dictionary->capacities[index] * sizeof(KeyValuePair));
        dictionary->keys[index] = realloc(dictionary->keys[index], dictionary->capacities[index] * sizeof(void*));
    }

    for (int i = 0; i < dictionary->counts[index]; ++i) {
        if (dictionary->keys[index][i] == key) {
            perror("\nITEM WITH SUCH KEY ALREADY EXISTS");
            return;
        }
    }

    KeyValuePair new_pair = {key, value};
    dictionary->keys[index][dictionary->counts[index]] = key;
    dictionary->array[index][dictionary->counts[index]++] = new_pair;
    ++dictionary->count;
}

/* returns a value by its key */
void* dict_resolve(Dictionary* dictionary, void* key) {
    size_t index = (long)key % 10;
    KeyValuePair* array = dictionary->array[index];

    for (int i = 0; i < dictionary->counts[index]; ++i) {
        if (array[i].key == key) {
            return array[i].value;
        }
    }

    perror("\nNO ITEM WITH SUCH KEY FOUND");
    return NULL;
}

void dict_remove(Dictionary* dictionary, void* key) {
    size_t index = (long)key % 10;
    KeyValuePair* array = dictionary->array[index];

    for (int i = 0; i < dictionary->counts[index]; ++i) {
        if (array[i].key == key) {
            for (int k = i; k < dictionary->counts[index] - 1; ++k) {
                array[i] = array[i + 1];
            }

            --dictionary->counts[index];
            --dictionary->count;
            return;
        }
    }

    perror("\nNO ITEM WITH SUCH KEY FOUND");
}

/* removes all items from dictionary, keeps capacities unchanged */
void dict_clear(Dictionary* dictionary) {
    for (int i = 0; i < 10; ++i) {
        dictionary->counts[i] = 0;
    }
    dictionary->count = 0;
}

/* completely deallocates dictionary */
void dict_dealloc(Dictionary* dictionary) {
    dict_clear(dictionary);
    for (int i = 0; i < 10; ++i) {
        dictionary->capacities[i] = 0;
    }

    free(dictionary->array);
}