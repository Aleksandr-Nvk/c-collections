#include <stdio.h>
#include "collections.h"
#include <string.h>

/* Examples of usage of all collections from collections.h */
int main(void) {

    /***************** LIST *****************/

    list my_list = new_list();          /* creating a list */
    char string[] = "Hello, world!";

    for (int i = 0; i < strlen(string); ++i) {   /* placing characters into the list */
        add_to_list(&my_list, &string[i]);
    }

    for (int i = 0; i < my_list.count; ++i) {   /* printing the items of the list */
        char* c = index_of_list(&my_list, i);
        printf("%c", *c);
    }

    return 0;
}