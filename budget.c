#include <stdio.h>
#include <string.h>
#include "budget.h"

char departmentNames[MAX_DEPARTMENTS][50];
float allocatedBudget[MAX_DEPARTMENTS];
float expenditure[MAX_DEPARTMENTS];

int budgetCount = 0;

void addBudget() {
    if (budgetCount >= MAX_DEPARTMENTS) {
        printf("Maximum departments reached.\n");
        return;
    }

    printf("Enter Department Name: ");
    scanf("%s", departmentNames[budgetCount]);
    
    do
    {
        printf("Enter Allocated Budget: ");
        scanf("%f", &allocatedBudget[budgetCount]);

        if (allocatedBudget[budgetCount] < 0) {
            printf("Budget cannot be negative\n");
        }
    } while (allocatedBudget[budgetCount] < 0);

    do {
        printf("Enter Expenditure: ");
        scanf("%f", &expenditure[budgetCount]);

        if (expenditure[budgetCount] < 0) {
            printf("Expenditure cannot be negative\n");
        }
    } while (expenditure[budgetCount] < 0);

    budgetCount++;
    printf("Budget Added Successfully\n");
}

void displayBudgets() {
    int i;

    if (budgetCount == 0) {
        printf("No budget records available.\n");
        return;
    }

    printf("\n--------BUDGET INFORMATION-------\n");

    for (i = 0; i < budgetCount; i++) {
        float remaining = allocatedBudget[i] - expenditure[i];

        printf("\nDepartment: %s\n", departmentNames[i]);
        printf("Allocated Budget: N$ %.2f\n", allocatedBudget[i]);
        printf("Expenditure: N$ %.2f\n", expenditure[i]);
        printf("Remaining Budget: N$ %.2f\n", remaining);

        if (remaining >= 0) {
            printf("Status: Within Budget\n");
        } else {
            printf("Status: Over Budget\n");
        }
    }
}

void checkBudgetStatus() {
    int i;
    int found = 0;

    printf("\nDepartments Exceeding Budget: \n");

    for (i = 0; i < budgetCount; i++) {
        if (expenditure[i] > allocatedBudget[i]) {
            printf("%s\n", departmentNames[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("No departments exceeded their budget.\n");
    }
} 
