#include <stdio.h>
#include <stdlib.h>
#include "collections.h"

/* returns a new blank stack */
Stack stack_new(void) {
    Stack new_stack = {NULL, 0, 0};
    return new_stack;
}

/* adds item to the top of stack */
void stack_push(Stack* stack, void* item) {
    if (stack == NULL) {
        perror("\nSTACK REFERENCE WAS NULL");
        return;
    }

    if (stack->capacity == 0) {          /* set default capacity if list is empty */
        stack->capacity = MIN_STACK_CAPACITY;
        stack->array = malloc(stack->capacity * sizeof(void*));
    } else if (stack->count == stack->capacity) {         /* double capacity of list if more space is needed */
        stack->capacity *= 2;
        stack->array = realloc(stack->array, stack->capacity * sizeof(void*));
    }

    stack->array[stack->count++] = item;
}

/* returns the last item from stack, removes it from stack */
void* stack_pop(Stack* stack) {
    if (stack == NULL) {
        perror("\nSTACK REFERENCE WAS NULL");
        return NULL;
    }

    if (stack->count != 0) {
        return stack->array[--stack->count];
    }

    perror("\nSTACK IS EMPTY");
    return NULL;
}

/* returns the last item from stack, keeps it in stack */
void* stack_peek(Stack* stack) {
    if (stack == NULL) {
        perror("\nSTACK REFERENCE WAS NULL");
        return NULL;
    }

    if (stack->count != 0) {
        return stack->array[stack->count - 1];
    }

    perror("\nSTACK IS EMPTY");
    return NULL;
}

/* removes all items from a list (capacity is unchanged) */
void stack_clear(Stack* stack) {
    if (stack == NULL) {
        perror("\nSTACK REFERENCE WAS NULL");
        return;
    }

    stack->count = 0;
}

/* completely deallocates stack */
void stack_dealloc(Stack* stack) {
    if (stack == NULL) {
        perror("\nSTACK REFERENCE WAS NULL");
        return;
    }

    stack->count = 0;
    stack->capacity = 0;

    free(stack->array);
}