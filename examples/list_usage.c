#include "collections.h"
#include <string.h>
#include <stdio.h>
#include "collections_generic.h"
#include <math.h>

typedef struct Employee {
    char* name;
    float salary;
} Employee;

int list_equals(Employee first, Employee second) {
    return fabsf(first.salary - second.salary) <= 0.01f && !strcmp(first.name, second.name);
}

int (*list_comp_func)(Employee, Employee) = &list_equals;

GENERATE_LIST_OF_TYPE(Employee, list_comp_func)

/* list usage: database of employees */
void list_execute_example(void) {
    EmployeeList list = Employee_list_new();

    Employee chandler = {"Chandler", 2500.0f};
    Employee phoebe = {"Phoebe", 1900.0f};
    Employee rachel = {"Rachel", 2000.0f};
    Employee ross = {"Ross", 900.0f};

    Employee_list_add(&list, chandler);
    Employee_list_add(&list, phoebe);
    Employee_list_add(&list, rachel);
    Employee_list_add(&list, ross);

    for (int i = 0; i < list.count; ++i) {
        Employee* employee = Employee_list_of_index(&list, i);
        if (strcmp(employee->name, "Ross") == 0) {
            employee->salary += 100.0f;             /* promote an employee with name 'Ross' */
            printf("\nRoss was promoted. Now he earns $%0.1f", employee->salary);
            break;
        }
    }

    Employee_list_remove(&list, chandler);              /* get a person sacked */

    for (int i = 0; i < list.count; ++i) {
        Employee* employee = Employee_list_of_index(&list, i);
        printf("\n%s earns $%0.1f", employee->name, employee->salary);
    }

    Employee_list_dealloc(&list);            /* mandatory deallocation of the list */
}