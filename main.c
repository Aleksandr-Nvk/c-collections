#include <stdio.h>
#include "list.h"
#include "linked_list.h"
#include <string.h>

/* Examples of usage of all collections from collections.h */
int main(void) {

    /***************** LIST *****************/

    printf("***************** LIST *****************\n\n");

    list my_list = new_list();          /* creating a list */
    char string_l[] = "Hello, world!";

    for (int i = 0; i < strlen(string_l); ++i) {   /* placing characters into the list */
        add_to_list(&my_list, &string_l[i]);
    }

    clear_list(&my_list);           /* practically recreating the list */

    for (int i = 0; i < strlen(string_l); ++i) {   /* placing characters into the list again */
        add_to_list(&my_list, &string_l[i]);
    }

    rem_fr_list(&my_list, index_of_list(&my_list, 4));    /* remove an item with index '4' */

    for (int i = 0; i < my_list.count; ++i) {    /* printing the items of the list */
        char* c = index_of_list(&my_list, i);
        printf("%c", *c);
    }

    rem_all_fr_list(&my_list);         /* nullify all items */

    printf("\n\n**********************************\n\n");

    /***************** LINKED LIST *****************/

    printf("***************** LINKED LIST *****************\n\n");

    linked_list my_lin_list = new_lin_list();   /* creating a linked list */
    char string_ll[] = "Another example!";

    printf("\n\n**********************************\n\n");

    return 0;
}