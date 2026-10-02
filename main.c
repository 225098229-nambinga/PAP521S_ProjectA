#include <stdio.h>

#include "Employee.h"
#include "assets.h"
#include "budget.h"
#include "reports.h"
#include "suppliers.h"

static int clearInputLine(void)
{
	int character;
	int extraInput = 0;

	while ((character = getchar()) != '\n' && character != EOF) {
		if (character != ' ' && character != '\t' && character != '\r') {
			extraInput = 1;
		}
	}
	return extraInput;
}

static int readChoice(int min, int max)
{
	int choice;
	int result;
	int extraInput;

	for (;;) {
		printf("Choice: ");
		result = scanf("%d", &choice);
		if (result == EOF) {
			printf("\nInput closed.\n");
			return -1;
		}

		extraInput = clearInputLine();
		if (result == 1 && !extraInput && choice >= min && choice <= max) {
			return choice;
		}
		printf("Invalid Input. Enter Input Again.\n");
	}
}

static int employeeMenu(void)
{
	int choice;

	do {
		printf("\n--- EMPLOYEE MANAGEMENT ---\n");
		printf("1. Add employee\n");
		printf("2. Display employees\n");
		printf("3. Search employees\n");
		printf("0. Back to main menu\n");
		choice = readChoice(0, 3);

		switch (choice) {
			case 1:
				addEmployee();
				break;
			case 2:
				displayEmployees();
				break;
			case 3:
				searchEmployee();
				break;
			case 0:
			case -1:
				break;
			default:
				printf("Invalid Input. Enter Input Again.\n");
		}
	} while (choice != 0 && choice != -1);
	return choice != -1;
}

static int budgetMenu(void)
{
	int choice;

	do {
		printf("\n--- BUDGET MANAGEMENT ---\n");
		printf("1. Add department budget\n");
		printf("2. Display budgets\n");
		printf("3. Check budget status\n");
		printf("0. Back to main menu\n");
		choice = readChoice(0, 3);

		switch (choice) {
			case 1:
				addBudget();
				break;
			case 2:
				displayBudgets();
				break;
			case 3:
				checkBudgetStatus();
				break;
			case 0:
			case -1:
				break;
			default:
				printf("Invalid Input. Enter Input Again.\n");
		}
	} while (choice != 0 && choice != -1);
	return choice != -1;
}

int main(void)
{
	int choice;

	do {
		printf("\n========================================\n");
		printf(" MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
		printf("========================================\n");
		printf("1. Employee Management\n");
		printf("2. Budget Management\n");
		printf("3. Supplier Management\n");
		printf("4. Asset Management\n");
		printf("5. Reports\n");
		printf("0. Exit\n");
		choice = readChoice(0, 5);

		switch (choice) {
			case 1:
				if (!employeeMenu()) {
					choice = -1;
				}
				break;
			case 2:
				if (!budgetMenu()) {
					choice = -1;
				}
				break;
			case 3:
				supplierMenu();
				break;
			case 4:
				assetMenu();
				break;
			case 5:
				reportsMenu();
				break;
			case 0:
				printf("Thanks For Using The Management System.\n");
				break;
			default:
				printf("Invalid Input. Enter Input Again.\n");
		}
	} while (choice != 0 && choice != -1);

	return 0;
}