/*C Program to read and print the n employee details using structure and dynamic memory allocation*/
#include <stdio.h>
#include <stdlib.h>
/*structure to hold the details of an employee*/
typedef struct employee
{
    int empId;
    char Name[100];
    char Designation[100];
    char Dept[10];

}employee_t;
/* Read the employee details using scanf*/
void readData(int n, employee_t* s)
{
    // Add your code here
    for(int i = 0; i < n; i++){
        printf("Employee ID:\n");
        scanf("%d", &s[i].empId);

        printf("Employee Name:\n");
        scanf("%s", &s[i].Name);

        printf("Designation: %c\n");
        scanf("%s", &s[i].Designation);

        printf("Department of employee: %c\n");
        scanf("%s", &s[i].Dept);

        s++;
        printf("\n");
    }
}
/* Function to print the employee details*/
void display(int n, employee_t * s)
{
    // Add your code here
    for(int i = 0; i < n; i++){
        printf("The details of the employee %d\n", i + 1);
        printf("Employee ID: %d\n", s[i].empId);
        printf("Employee Name: %s\n", s[i].Name);
        printf("Designation: %s\n", s[i].Designation);
        printf("Department of employee: %s\n", s[i].Dept);

        s++;
        printf("\n");
    }
}

/*----------Main Program--------*/
int main()

{
    // Main Function to print the employee details
    // Add your code here

    int n; 
    printf("Enter the numbers of employees: ");
    scanf("%d", &n);

    employee_t* employees = (employee_t*)malloc(n*sizeof(employee_t));
    if(employees == NULL) return -1;

    readData(n, employees);
    display(n, employees);

    free(employees);

    return 0;
}

