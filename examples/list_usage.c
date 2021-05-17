#include "collections.h"
#include <string.h>
#include <stdio.h>

/* list usage: database of employees */
void list_execute_example(void) {
    typedef struct Employee {
        char* name;
        float salary;
    } Employee;

    List list = list_new();

    Employee chandler = {"Chandler", 2500.0f};
    Employee phoebe = {"Phoebe", 1900.0f};
    Employee rachel = {"Rachel", 2000.0f};
    Employee ross = {"Ross", 900.0f};

    list_add(&list, &chandler);
    list_add(&list, &phoebe);
    list_add(&list, &rachel);
    list_add(&list, &ross);

    for (int i = 0; i < list.count; ++i) {
        Employee* employee = (Employee*)list_of_index(&list, i);
        if (strcmp(employee->name, "Ross") == 0) {
            employee->salary += 100.0f;             /* promote an employee with name 'Chandler' */
            printf("\nRoss was promoted. Now he earns $%0.1f", employee->salary);
            break;
        }
    }

    list_remove(&list, &chandler);              /* get a person sacked */

    for (int i = 0; i < list.count; ++i) {
        Employee* employee = (Employee*)list_of_index(&list, i);
        printf("\n%s earns $%0.1f", employee->name, employee->salary);
    }

    list_dealloc(&list);            /* mandatory deallocation of the list */
}