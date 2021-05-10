#include <stdio.h>
#include "list.h"
#include "linked_list.h"
#include "stack.h"
#include <string.h>

/* prints linked list content recursively */
void lin_list_print(Node* head);

/* reverses string and returns it */
char* str_reverse(const char* string, size_t length);

/* Examples of usage of all collections */
int main(void) {

    printf("\n\n***************** LIST *****************\n\n");

    List my_list = list_new();          /* creating a list */
    char string_l[] = "Hello, world!";

    for (int i = 0; i < strlen(string_l); ++i) {   /* placing characters into the list */
        list_add(&my_list, &string_l[i]);
    }

    list_clear(&my_list);         /* nullify all items */

    for (int i = 0; i < strlen(string_l); ++i) {   /* placing characters into the list again */
        list_add(&my_list, &string_l[i]);
    }

    list_remove(&my_list, list_of_index(&my_list, 4));    /* remove an item with index '4' */

    for (int i = 0; i < my_list.count; ++i) {    /* printing the items of the list */
        char* c = list_of_index(&my_list, i);
        printf("%c", *c);
    }

    list_dealloc(&my_list);           /* deallocating the list */

    printf("\n\n***************** LINKED LIST *****************\n\n");

    char string_ll[] = "example!";
    Node* head = lin_list_new_head(&string_ll[0]);  /* creating a head Node */

    for (int i = 1; i < strlen(string_ll); ++i) {
        lin_list_append(head, &string_ll[i]);  /* implicit creation of nodes and appending to the chain */
    }

    lin_list_print(head);          /* printing data from the linked list recursively */
    printf("\n");

    char* string_ll_1 = "Another ";
    string_ll_1 = str_reverse(string_ll_1, strlen(string_ll_1));

    Node* new_head = head;

    for (int i = 0; i < strlen(string_ll_1); ++i) {     /* implicit creation of nodes and prepending to the chain */
        new_head = lin_list_prepend(new_head, &string_ll_1[i]);
    }

    lin_list_print(new_head);
    printf("\n");

    char* string_ll_2 = " 'garbage line!'";          /* just an example of string we want to remove */

    for (int i = 0; i < strlen(string_ll_2); ++i) {
        lin_list_append(new_head, &string_ll_2[i]);          /* adding garbage string */
    }

    lin_list_print(new_head);
    printf("\n");

    for (int i = 0; i < strlen(string_ll_2); ++i) {
        lin_list_remove_tail(new_head);           /* removing garbage string */
    }

    for (int i = 0; i < 2; ++i) {
        new_head = lin_list_remove_head(new_head);   /* removing items from head */
    }

    lin_list_remove(new_head, &string_ll[7]);     /* remove a node by value */

    lin_list_print(new_head);

    lin_list_dealloc(new_head);        /* deallocate all nodes starting from 'new_head' */

    printf("\n\n***************** STACK *****************\n\n");

    Stack new_stack = stack_new();
    char* st_string = "!kcab detnirp dna kcats ni derots saw I esuaceb desrever m'I";

    for (int i = 0; i < strlen(st_string); ++i) {
        push(&new_stack, &st_string[i]);            /* putting an item to the top of stack */
    }

    while (new_stack.count > 0) {
        char* c = pop(&new_stack);          /* taking an item from the top of stack */
        putchar(*c);
    }

    printf("\nNow stack has %zu items", new_stack.count);

    stack_dealloc(&new_stack);          /* deallocating stack */

    return 0;
}

void lin_list_print(Node* head) {
    if (head != NULL) {
        char* data = head->data;
        printf("%c", *data);

        if (head->next != NULL) {
            lin_list_print(head->next);
        }
    }
}

char* str_reverse(const char* string, size_t length) {
    char* reversed = malloc(length + 1);
    int i = 0;

    for (; i < length; ++i) {
        reversed[i] = string[length - 1 - i];
    }
    reversed[i] = '\0';

    return reversed;
}