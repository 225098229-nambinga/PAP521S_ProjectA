#ifndef BUDGET_H
#define BUDGET_H

#define MAX_BUDGET 50

/* Parallel arrays */
extern char  budgetDept[MAX_BUDGET][50];
extern float budgetAllocated[MAX_BUDGET];
extern float budgetSpent[MAX_BUDGET];
extern int   budgetCount;

/* Function prototypes */
void budgetMenu(void);
void addBudget(void);
void enterExpenditure(void);
void displayBudgets(void);
void showExceededBudgets(void);
float calculateRemaining(float allocated, float spent);
int  findBudget(char dept[]);

#endif