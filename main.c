#include <stdio.h>
#include "list.h"
#include "linked_list.h"
#include <string.h>

/* prints linked list content recursively */
void print_lin_list(node* current);

/* reverses str and returns it */
char* str_rev(const char* str, size_t len);

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

    char string_ll[] = "example!";
    node* head = new_lin_list_head(&string_ll[0]);  /* creating a head node */

    for (int i = 1; i < strlen(string_ll); ++i) {
        ap_to_lin_list(head, &string_ll[i]);  /* implicit creation of nodes and appending to the chain */
    }

    print_lin_list(head);          /* printing data from the linked list recursively */
    printf("\n");

    char* string_ll_1 = "Another ";
    string_ll_1 = str_rev(string_ll_1, strlen(string_ll_1));

    node* new_head = head;

    for (int i = 0; i < strlen(string_ll_1); ++i) {
        new_head = prep_to_lin_list(new_head, &string_ll_1[i]);  /* implicit creation of nodes and prepending to the chain */
    }

    print_lin_list(new_head);
    printf("\n");

    char* string_ll_2 = " 'garbage line!'";          /* just an example of string we want to remove */

    for (int i = 0; i < strlen(string_ll_2); ++i) {
        ap_to_lin_list(new_head, &string_ll_2[i]);          /* adding garbage string */
    }

    print_lin_list(new_head);
    printf("\n");

    for (int i = 0; i < strlen(string_ll_2); ++i) {
        rem_fr_end_of_lin_list(new_head);           /* removing garbage string */
    }

    for (int i = 0; i < 2; ++i) {
        new_head = rem_at_head_of_lin_list(new_head);   /* removing items from head */
    }

    print_lin_list(new_head);

    clear_lin_list(new_head);        /* deallocate all nodes starting from 'new_head' */

    printf("\n\n**********************************\n\n");

    return 0;
}

void print_lin_list(node* current) {
    if (current != NULL) {
        char* data = current->data;
        printf("%c", *data);

        if (current->next != NULL) {
            print_lin_list(current->next);
        }
    }
}

char* str_rev(const char* str, size_t len) {
    char* reversed = malloc(len + 1);
    int i = 0;

    for (; i < len; ++i) {
        reversed[i] = str[len - 1 - i];
    }
    reversed[i] = '\0';

    return reversed;
}