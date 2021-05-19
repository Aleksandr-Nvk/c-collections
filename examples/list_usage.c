#include <stdio.h>
#include <string.h>
#include <math.h>
#include "collections_generic.h"

/* dummy Employee structure example */
typedef struct Employee {
    char* name;
    float salary;
} Employee;

int list_equals(Employee first, Employee second);

GENERATE_LIST_OF_TYPE(Employee, &list_equals)   /* 1. generate API for list */

void print_list(EmployeeList list);

/* list usage: database of employees */
void list_execute_example(void) {
    Employee chandler = {"Chandler", 2500.0f};
    Employee phoebe = {"Phoebe", 1900.0f};
    Employee rachel = {"Rachel", 2000.0f};
    Employee ross = {"Ross", 900.0f};

    EmployeeList list = Employee_list_new();            /* 2. create a new list */

    printf("\n*** INITIAL ***\n");
    print_list(list);

    Employee_list_add(&list, chandler);             /* 3. add copy of 'chandler' to list */
    Employee_list_add(&list, phoebe);           /* 3. add copy of 'phoebe' to list */
    Employee_list_add(&list, rachel);           /* 3. add copy of 'rachel' to list */
    Employee_list_add(&list, ross);             /* 3. add copy of 'ross' to list */

    printf("\n\n*** ADDED ***\n");
    print_list(list);

    Employee_list_remove(&list, chandler);          /* 3. remove item identical to 'chandler' */
    ross.salary = 50000.0f;
    Employee_list_remove(&list, ross);          /* 3. removal fails because 'ross' in list has a different salary */

    printf("\n\n*** REMOVED ***\n");
    print_list(list);

    Employee_list_clear(&list);             /* 3. remove all items, keep capacity */

    printf("\n\n*** CLEARED ***\n");
    print_list(list);

    Employee_list_dealloc(&list);            /* 4. deallocate the list (to avoid memory leak) */
}

/* function used to compare objects in list */
int list_equals(Employee first, Employee second) {
    return fabsf(first.salary - second.salary) <= 0.01f && !strcmp(first.name, second.name);
}

/* prints every item with description, count and capacity */
void print_list(EmployeeList list) {
    for (int i = 0; i < list.count; ++i) {
        Employee* employee = Employee_list_of_index(&list, i);    /* 3. resolve POINTER to item by index */
        printf("\n%s earns $%.0f", employee->name, employee->salary);
    }

    printf("\n\nCount: %zu", list.count);
    printf("\nCapacity: %zu", list.capacity);
}