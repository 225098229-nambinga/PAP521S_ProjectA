#include <stdio.h>
#include <string.h>
#include "Employee.h"

#define MAX 100   // Maximum employees we can store

// Arrays to hold employee details
int   empID[MAX];
char  empName[MAX][50];
char  empDept[MAX][50];
char  empPosition[MAX][50];
char  empPhone[MAX][20];
float empBasic[MAX];
float empHousing[MAX];
float empTransport[MAX];
int   empCount = 0;   // How many employees we currently have


// Add basic + housing + transport to get gross salary
float calculateSalary(float basic, float housing, float transport)
{
    return basic + housing + transport;
}


// Looking for an employee by ID.
// Returns the position in the array or -1 if not found.
int findEmployee(int searchID)
{
    for (int i = 0; i < empCount; i++) {
        if (empID[i] == searchID) {
            return i;
        }
    }
    return -1;
}


// Ask the user for employee details and save them
void addEmployee()
{
    // Stop if we reached the limit
    if (empCount >= MAX) {
        printf("The employee list is full.\n");
        return;
    }

    int newID;
    printf("\n-- Add Employee --\n");
    printf("ID: ");
    scanf("%d", &newID);

    // ID must be positive and not already used
    if (newID <= 0) {
        printf("ID must be a positive number.\n");
        return;
    }
    if (findEmployee(newID) != -1) {
        printf("That ID is already taken.\n");
        return;
    }

    empID[empCount] = newID;

    printf("Name: ");
    scanf("%49s", empName[empCount]);

    printf("Department: ");
    scanf("%49s", empDept[empCount]);

    printf("Position: ");
    scanf("%49s", empPosition[empCount]);

    printf("Phone: ");
    scanf("%19s", empPhone[empCount]);

    // Salaries and allowances cannot be negative

    printf("Basic salary: ");
    scanf("%f", &empBasic[empCount]);
    if (empBasic[empCount] < 0) {
        printf("Salary cannot be negative.\n");
        return;
    }

    printf("Housing allowance: ");
    scanf("%f", &empHousing[empCount]);
    if (empHousing[empCount] < 0) {
        printf("Allowance cannot be negative.\n");
        return;
    }

    printf("Transport allowance: ");
    scanf("%f", &empTransport[empCount]);
    if (empTransport[empCount] < 0) {
        printf("Allowance cannot be negative.\n");
        return;
    }

    // Move to the next free slot
    empCount++;
    printf("Employee saved.\n");
}


// Show all employees in a table
void displayEmployees()
{
    if (empCount == 0) {
        printf("\nNo employees registered yet.\n");
        return;
    }

    printf("\n-- All Employees --\n");
    printf("%-6s %-15s %-15s %-15s %-12s %-10s %-10s %-10s %-10s\n",
           "ID", "Name", "Department", "Position", "Phone",
           "Basic", "Housing", "Transport", "Total");

    // Loop through every employee and print one row
    for (int i = 0; i < empCount; i++) {
        printf("%-6d %-15s %-15s %-15s %-12s %-10.2f %-10.2f %-10.2f %-10.2f\n",
               empID[i],
               empName[i],
               empDept[i],
               empPosition[i],
               empPhone[i],
               empBasic[i],
               empHousing[i],
               empTransport[i],
               calculateSalary(empBasic[i], empHousing[i], empTransport[i]));
    }
}


// Search by ID and show that employee details
void searchEmployee()
{
    if (empCount == 0) {
        printf("\nNo employees to search.\n");
        return;
    }

    int searchID;
    printf("\n-- Search Employee --\n");
    printf("ID: ");
    scanf("%d", &searchID);

    // findEmployee returns the position or -1 if not found
    int index = findEmployee(searchID);

    if (index == -1) {
        printf("No employee with ID %d.\n", searchID);
        return;
    }

    printf("\nEmployee Found:\n");
    printf("ID:         %d\n",   empID[index]);
    printf("Name:       %s\n",   empName[index]);
    printf("Department: %s\n",   empDept[index]);
    printf("Position:   %s\n",   empPosition[index]);
    printf("Phone:      %s\n",   empPhone[index]);
    printf("Basic:      %.2f\n", empBasic[index]);
    printf("Housing:    %.2f\n", empHousing[index]);
    printf("Transport:  %.2f\n", empTransport[index]);
    printf("Total:      %.2f\n", calculateSalary(empBasic[index], empHousing[index], empTransport[index]));
} 


