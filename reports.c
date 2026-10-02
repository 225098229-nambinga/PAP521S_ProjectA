#include <stdio.h>
#include <string.h>
#include "assets.h"
#include "budget.h"
#include "Employee.h"
#include "reports.h"
#include "suppliers.h"

void reportsMenu(void)
{
    int choice = 0;

    do {
        printf("\n========================================\n");
        printf("                REPORTS MENU\n");
        printf("========================================\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Asset Report\n");
        printf("4. Supplier Report\n");
        printf("5. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);
        while (getchar() != '\n') {
        }

        switch (choice) {
            case 1:
                employeeReport();
                break;
            case 2:
                budgetReport();
                break;
            case 3:
                assetReport();
                break;
            case 4:
                supplierReport();
                break;
            case 5:
                printf("Returning to the main menu...\n");
                break;
            default:
                printf("Invalid option. Please choose again.\n");
                break;
        }
    } while (choice != 5);
}

void employeeReport(void)
{
    int i;
    int highestIndex = -1;
    int lowestIndex = -1;
    float totalBasic = 0.0f;
    float totalPayroll = 0.0f;
    char departments[50][50];
    int departmentCount[50];
    int uniqueDepartments = 0;

    if (empCount == 0) {
        printf("\nNo employee records available.\n");
        return;
    }

    for (i = 0; i < empCount; i++) {
        float gross = calculateSalary(empBasic[i], empHousing[i], empTransport[i]);

        totalBasic += empBasic[i];
        totalPayroll += gross;

        if (highestIndex == -1 || gross > calculateSalary(empBasic[highestIndex], empHousing[highestIndex], empTransport[highestIndex])) {
            highestIndex = i;
        }

        if (lowestIndex == -1 || gross < calculateSalary(empBasic[lowestIndex], empHousing[lowestIndex], empTransport[lowestIndex])) {
            lowestIndex = i;
        }

        int found = 0;
        for (int j = 0; j < uniqueDepartments; j++) {
            if (strcmp(empDept[i], departments[j]) == 0) {
                departmentCount[j]++;
                found = 1;
                break;
            }
        }

        if (!found) {
            strcpy(departments[uniqueDepartments], empDept[i]);
            departmentCount[uniqueDepartments] = 1;
            uniqueDepartments++;
        }
    }

    printf("\n================ EMPLOYEE REPORT ================\n");
    printf("Total employees: %d\n", empCount);
    printf("Total basic salary: N$ %.2f\n", totalBasic);
    printf("Total payroll: N$ %.2f\n", totalPayroll);
    printf("Highest salaried employee: %s (N$ %.2f)\n", empName[highestIndex], calculateSalary(empBasic[highestIndex], empHousing[highestIndex], empTransport[highestIndex]));
    printf("Lowest salaried employee: %s (N$ %.2f)\n", empName[lowestIndex], calculateSalary(empBasic[lowestIndex], empHousing[lowestIndex], empTransport[lowestIndex]));

    printf("\nDepartment summary:\n");
    printf("%-20s %-8s\n", "Department", "Count");
    for (i = 0; i < uniqueDepartments; i++) {
        printf("%-20s %-8d\n", departments[i], departmentCount[i]);
    }
}

void budgetReport(void)
{
    int i;
    float totalAllocated = 0.0f;
    float totalSpending = 0.0f;
    float totalRemaining = 0.0f;

    if (budgetCount == 0) {
        printf("\nNo budget records available.\n");
        return;
    }

    printf("\n================ BUDGET REPORT ================\n");
    printf("%-20s %-15s %-15s %-15s %-10s\n", "Department", "Allocated", "Spent", "Remaining", "Status");
    printf("--------------------------------------------------------------------\n");

    for (i = 0; i < budgetCount; i++) {
        float remaining = allocatedBudget[i] - expenditure[i];
        const char *status = (remaining >= 0.0f) ? "On Track" : "Over Budget";

        totalAllocated += allocatedBudget[i];
        totalSpending += expenditure[i];
        totalRemaining += remaining;

        printf("%-20s %-15.2f %-15.2f %-15.2f %-10s\n",
               departmentNames[i],
               allocatedBudget[i],
               expenditure[i],
               remaining,
               status);
    }

    printf("--------------------------------------------------------------------\n");
    printf("%-20s %-15.2f %-15.2f %-15.2f\n",
           "TOTAL",
           totalAllocated,
           totalSpending,
           totalRemaining);
}

void assetReport(void)
{
    int i;
    float totalValue = 0.0f;
    int goodCondition = 0;
    int fairCondition = 0;
    int poorCondition = 0;

    if (assetCount == 0) {
        printf("\nNo asset records available.\n");
        return;
    }

    for (i = 0; i < assetCount; i++) {
        totalValue += assets[i].purchaseValue;

        if (strcmp(assets[i].condition, "Good") == 0 || strcmp(assets[i].condition, "good") == 0) {
            goodCondition++;
        } else if (strcmp(assets[i].condition, "Fair") == 0 || strcmp(assets[i].condition, "fair") == 0) {
            fairCondition++;
        } else if (strcmp(assets[i].condition, "Poor") == 0 || strcmp(assets[i].condition, "poor") == 0) {
            poorCondition++;
        }
    }

    printf("\n================ ASSET REPORT ================\n");
    printf("Total assets: %d\n", assetCount);
    printf("Total asset value: N$ %.2f\n", totalValue);
    printf("Condition summary: Good=%d, Fair=%d, Poor=%d\n", goodCondition, fairCondition, poorCondition);

    printf("\n%-10s %-20s %-18s %-12s %-15s\n",
           "ID",
           "Name",
           "Type",
           "Value",
           "Department");
    printf("--------------------------------------------------------------------\n");

    for (i = 0; i < assetCount; i++) {
        printf("%-10d %-20.20s %-18.18s %-12.2f %-15.15s\n",
               assets[i].assetID,
               assets[i].assetName,
               assets[i].assetType,
               assets[i].purchaseValue,
               assets[i].department);
    }
}

void supplierReport(void)
{
    int i;

    printf("\n=============== SUPPLIER REPORT ===============\n");
    printf("Total suppliers: %d\n", supplierCount);

    if (supplierCount == 0) {
        printf("No suppliers registered.\n");
        return;
    }

    printf("%-10s %-18s %-25s %-16s %-15s\n",
           "ID",
           "Name",
           "Email",
           "Phone",
           "Town");
    printf("-------------------------------------------------------------------\n");

    for (i = 0; i < supplierCount; i++) {
        printf("%-10s %-18.18s %-25.25s %-16.16s %-15.15s\n",
               supplierID[i],
               supplierName[i],
               supplierEmail[i],
               supplierPhone[i],
               supplierTown[i]);
    }
}

 
