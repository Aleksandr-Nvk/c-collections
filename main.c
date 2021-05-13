#include <stdio.h>
#include <string.h>
#include "list.h"
#include "linked_list.h"
#include "stack.h"
#include "queue.h"
#include "dictionary.h"

/* prints linked list content recursively */
void lin_list_print(Node* head) {
    if (head != NULL) {
        char* data = head->data;
        printf("%c", *data);

        if (head->next != NULL) {
            lin_list_print(head->next);
        }
    }
}

/* reverses string and returns it */
char* str_reverse(const char* string, size_t length) {
    char* reversed = malloc(length + 1);
    int i = 0;

    for (; i < length; ++i) {
        reversed[i] = string[length - 1 - i];
    }
    reversed[i] = '\0';

    return reversed;
}

/* Examples of usage of all collections */
int main(void) {

    printf("\n\n***************** LIST *****************\n\n");

    List list = list_new();          /* creating a new list */
    char* list_string = "Exam";

    for (int i = 0; i < strlen(list_string); ++i) {
        list_add(&list, &list_string[i]);
    }

    list_remove(&list, &list_string[0]);

    for (int i = 0; i < list.count; ++i) {
        putchar(*(char*)list_of_index(&list, i));
    }

    list_dealloc(&list);           /* deallocating the list using list API */

    printf("\n\n***************** LINKED LIST *****************\n\n");

    char string_ll[] = "example!";
    Node* head = lin_list_new_head(&string_ll[0]);  /* creating a head Node */

    for (int i = 1; i < strlen(string_ll); ++i) {
        lin_list_append(head, &string_ll[i]);  /* implicit creation of nodes and appending to the chain */
    }

    lin_list_print(head);          /* printing data from the linked list recursively */
    putchar('\n');

    char* string_ll_1 = "Another ";
    string_ll_1 = str_reverse(string_ll_1, strlen(string_ll_1));

    Node* new_head = head;

    for (int i = 0; i < strlen(string_ll_1); ++i) {     /* implicit creation of nodes and prepending to the chain */
        new_head = lin_list_prepend(new_head, &string_ll_1[i]);
    }

    lin_list_print(new_head);
    putchar('\n');

    char* string_ll_2 = " 'garbage line!'";          /* just an example of string we want to remove */

    for (int i = 0; i < strlen(string_ll_2); ++i) {
        lin_list_append(new_head, &string_ll_2[i]);          /* adding garbage string */
    }

    lin_list_print(new_head);
    putchar('\n');

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

    Stack stack = stack_new();
    char* st_string = "!kcab detnirp dna kcats ni derots saw I esuaceb desrever m'I";

    for (int i = 0; i < strlen(st_string); ++i) {
        push(&stack, &st_string[i]);            /* putting an item to the top of stack */
    }

    while (stack.count > 0) {
        char* c = stack_pop(&stack);          /* taking an item from the top of stack */
        putchar(*c);
    }

    printf("\nNow stack has %zu items", stack.count);

    stack_dealloc(&stack);          /* deallocating stack */

    printf("\n\n***************** QUEUE *****************\n\n");

    Queue queue = queue_new();          /* creating a new queue */
    char qu_string[] = "Queue example!";

    for (int i = 0; i < strlen(qu_string); ++i) {
        queue_enqueue(&queue, &qu_string[i]);   /* putting chars into a queue */
    }

    for (int i = 0; i < queue.count; ++i) {
        char* c = queue_peek(&queue);    /* getting only the next item without removing it from the queue */
        putchar(*c);
    }

    putchar('\n');

    while (queue.count > 0) {
        char* c = queue_dequeue(&queue);    /* getting items and removing them from the queue */
        putchar(*c);
    }

    queue_clear(&queue);            /* removing all items from the queue (makes no sense here, just an example) */

    queue_dealloc(&queue);          /* completely deallocating the queue */

    printf("\n\n***************** DICTIONARY (HASH TABLE) *****************\n\n");

    Dictionary dictionary = dict_new();   /* creating a new dictionary */
    short keys[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    char* values[] = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};

    for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); ++i) {
        dict_add(&dictionary, &keys[i], values[i]);   /* adding values and their keys to dictionary */
    }

    dict_remove(&dictionary, &keys[8]);   /* removing '8-"Eight"' pair */

    printf("%s\n", (char*) dict_resolve(&dictionary, &keys[2]));
    printf("%s\n", (char*) dict_resolve(&dictionary, &keys[8]));     /* printing the 8th digit */

    dict_clear(&dictionary);

    dict_dealloc(&dictionary);

    return 0;
}
