#include "collections_generic.h"

GENERATE_DICTIONARY_OF_TYPE(int, float)

/* dictionary usage: building tables with data bond to keys */
void dictionary_execute_example(void) {
    int age;
    float height;
    intfloatDictionary dictionary = int_value_type_dict_new();

    int_value_type_dict_add(&dictionary, 14, 158.7f);         /* table data from web */
    int_value_type_dict_add(&dictionary, 15, 159.7f);
    int_value_type_dict_add(&dictionary, 16, 162.5f);
    int_value_type_dict_add(&dictionary, 17, 162.5f);
    int_value_type_dict_add(&dictionary, 18, 163.0f);
    int_value_type_dict_add(&dictionary, 19, 163.3f);

    printf("\nEnter your age (between 14 and 19 inclusively) and press Enter: ");
    scanf("%d", &age);          /* didn't use strtol() for the sake of brevity */

    height = int_value_type_dict_resolve(&dictionary, age);
    printf("\nYou are %d y.o., and your normal height should be %.1f", age, height);

    int_value_type_dict_dealloc(&dictionary);           /* mandatory deallocation of the dictionary */
}