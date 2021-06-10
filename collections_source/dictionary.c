#include <stdlib.h>
#include <stdio.h>

#define MIN_CAPACITY 4  /* default capacity of internal dictionary arrays when you add the first items to them */

typedef struct KeyValuePair {
    void* key;
    void* value;
} KeyValuePair;

typedef struct Dictionary {
    KeyValuePair** array;           /* array of 10 arrays, basic structure of hash table */

    size_t* counts;         /* stores 10 counts of each nested array */
    size_t* capacities;         /* stores 10 capacities of each nested array */

    size_t count;            /* amount of key-value pairs currently stored in dictionary */
} Dictionary;

Dictionary dict_new(void) {
    size_t pair, other;
    pair = sizeof(KeyValuePair*);
    other = sizeof(size_t);
    Dictionary new_dictionary = {malloc(10 * pair),calloc(10, other),calloc(10, other),0};

    return new_dictionary;
}

/* adds a key-value pair to a dictionary */
void dict_add(Dictionary* dictionary, void* key, void* value) {
    if (dictionary == NULL) {
        perror("\nDICTIONARY REFERENCE WAS NULL");
        return;
    }
    if (key == NULL) {
        perror("\nKEY WAS NULL");
        return;
    }

    size_t index = (long)key % 10;          /* reduce the amount of indices */

    if (dictionary->capacities[index] == 0) {
        dictionary->capacities[index] = MIN_CAPACITY;
        dictionary->array[index] = malloc(dictionary->capacities[index] * sizeof(KeyValuePair));
    } else if (dictionary->capacities[index] == dictionary->counts[index]) {
        dictionary->capacities[index] *= 2;
        dictionary->array[index] = realloc(dictionary->array[index], dictionary->capacities[index] * sizeof(KeyValuePair));
    }

    for (int i = 0; i < dictionary->counts[index]; ++i) {
        if (dictionary->array[index][i].key == key) {
            perror("\nITEM WITH SUCH KEY ALREADY EXISTS");
            return;
        }
    }

    KeyValuePair new_pair = {key, value};
    dictionary->array[index][dictionary->counts[index]++] = new_pair;
    ++dictionary->count;
}

/* returns a value by its key */
void* dict_resolve(Dictionary* dictionary, void* key) {
    if (dictionary == NULL) {
        perror("\nDICTIONARY REFERENCE WAS NULL");
        return NULL;
    }
    if (key == NULL) {
        perror("\nKEY WAS NULL");
        return NULL;
    }

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

/* removes a value bond to a key from a dictionary */
void dict_remove(Dictionary* dictionary, void* key) {
    if (dictionary == NULL) {
        perror("\nDICTIONARY REFERENCE WAS NULL");
        return;
    }
    if (key == NULL) {
        perror("\nKEY WAS NULL");
        return;
    }

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
}

/* removes all items from a dictionary (capacity is unchanged) */
void dict_clear(Dictionary* dictionary) {
    if (dictionary == NULL) {
        perror("\nDICTIONARY REFERENCE WAS NULL");
        return;
    }

    for (int i = 0; i < 10; ++i) {
        dictionary->counts[i] = 0;
    }
    dictionary->count = 0;
}

/* completely deallocates dictionary */
void dict_dealloc(Dictionary* dictionary) {
    if (dictionary == NULL) {
        perror("\nDICTIONARY REFERENCE WAS NULL");
        return;
    }

    dict_clear(dictionary);

    for (int i = 0; i < 10; ++i) {
        dictionary->capacities[i] = 0;
    }

    free(dictionary->array);
}