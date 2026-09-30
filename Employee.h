#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#define MAX 100          // Maximum employees we can store

/* Parallel arrays – only declared here */
extern int   empID[MAX];
extern char  empName[MAX][50];
extern char  empDept[MAX][50];
extern char  empPosition[MAX][50];
extern char  empPhone[MAX][20];
extern float empBasic[MAX];
extern float empHousing[MAX];
extern float empTransport[MAX];
extern int   empCount;

// Function prototypes for the employee module
float calculateSalary(float basic, float housing, float transport);
int findEmployee(int searchID);
void addEmployee();
void displayEmployees();
void searchEmployee();

#endif