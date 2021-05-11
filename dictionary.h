#include <stdlib.h>

#define MIN_CAPACITY 4  /* min capacity an array is expanded to when You add an item to a zero-capacity list */

typedef struct KeyValuePair {
    void* key;
    void* value;
} KeyValuePair;

typedef struct Dictionary {
    KeyValuePair** array;           /* array of 10 arrays, basic structure of hash table */
    size_t* counts;         /* stores 10 counts of each nested array */
    size_t* capacities;         /* stores 10 capacities of each nested array */

    size_t count;            /* amount of key-value pairs currently stored in array */
} Dictionary;

Dictionary dictionary_new() {
    Dictionary new_dictionary = {malloc(10 * sizeof(KeyValuePair*)), calloc(10, sizeof(size_t)),
                                 calloc(10, sizeof(size_t)), 0};

    return new_dictionary;
}

void dictionary_add(Dictionary* dictionary, void* key, void* value) {
    size_t index = (long)key % 10;

    if (dictionary->capacities[index] == 0) {
        dictionary->capacities[index] = MIN_CAPACITY;
        dictionary->array[index] = malloc(dictionary->capacities[index] * sizeof(KeyValuePair));
    } else if (dictionary->capacities[index] == dictionary->counts[index]) {
        dictionary->capacities[index] *= 2;
        dictionary->array[index] = realloc(dictionary->array[index], dictionary->capacities[index] * sizeof(KeyValuePair));
    }

    KeyValuePair new_pair = {key, value};
    dictionary->array[index][dictionary->counts[index]++] = new_pair;
    ++dictionary->count;
}

void* dictionary_resolve(Dictionary* dictionary, void* key) {
    size_t index = (long)key % 10;
    KeyValuePair* array = dictionary->array[index];

    for (int i = 0; i < dictionary->counts[index]; ++i) {
        if (array[i].key == key) {
            return array[i].value;
        }
    }

    perror("NO ITEM WITH SUCH KEY");
    return NULL;
}