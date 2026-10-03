#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPARTMENTS 50

extern char departmentNames[MAX_DEPARTMENTS][50];
extern float allocatedBudget[MAX_DEPARTMENTS];
extern float expenditure[MAX_DEPARTMENTS];
extern int budgetCount;

void addBudget(void);
void displayBudgets(void);
void checkBudgetStatus(void);

#endif
