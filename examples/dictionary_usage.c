#include "collections_generic.h"

int dict_equals(int first, int second);

GENERATE_DICTIONARY_OF_TYPE(int, float, &dict_equals)           /* 1. generate API for dictionary */

/* dictionary usage: building tables with data bond to keys */
void dictionary_execute_example(void) {
    int age;
    float height;
    intfloatDictionary dictionary = intfloat_dict_new();            /* 2. create a new dictionary */

    intfloat_dict_add(&dictionary, 14, 158.7f);         /* 3. add table data from web */
    intfloat_dict_add(&dictionary, 15, 159.7f);
    intfloat_dict_add(&dictionary, 16, 162.5f);
    intfloat_dict_add(&dictionary, 17, 162.5f);
    intfloat_dict_add(&dictionary, 18, 163.0f);
    intfloat_dict_add(&dictionary, 19, 163.3f);

    intfloat_dict_remove(&dictionary, 19);          /* 3. remove the last line from the table */

    printf("\nEnter your age (between 14 and 18 inclusively) and press Enter: ");
    scanf("%d", &age);          /* didn't use strtol() for the sake of brevity */

    height = intfloat_dict_resolve(&dictionary, age);           /* 3. get a value by its key */
    printf("\nYou are %d y.o., and your normal height should be %.1f", age, height);

    intfloat_dict_clear(&dictionary);           /* remove all items from the dictionary (redundant in this example) */

    intfloat_dict_dealloc(&dictionary);           /* 4. deallocate the dictionary (to avoid memory leak) */
}

/* function used to compare objects in dictionaries */
int dict_equals(int first, int second) {
    return first == second;
}