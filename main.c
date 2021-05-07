#include <stdio.h>
#include "list.h"
#include <string.h>

/* Examples of usage of all collections from collections.h */
int main(void) {

    /***************** LIST *****************/

    list my_list = new_list();          /* creating a list */
    char string[] = "Hello, world!";

    for (int i = 0; i < strlen(string); ++i) {   /* placing characters into the list */
        add_to_list(&my_list, &string[i]);
    }

    clear_list(&my_list);           /* practically recreating the list */

    for (int i = 0; i < strlen(string); ++i) {   /* placing characters into the list again */
        add_to_list(&my_list, &string[i]);
    }

    remove_from_list(&my_list, index_of_list(&my_list, 4));    /* remove an item with index '4' */

    for (int i = 0; i < my_list.count; ++i) {    /* printing the items of the list */
        char* c = index_of_list(&my_list, i);
        printf("%c", *c);
    }

    remove_all_from_list(&my_list);         /* nullify all items */

    return 0;
}