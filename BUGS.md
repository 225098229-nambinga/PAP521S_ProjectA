# BUG TRACKING LOG — MFMS Project A

## Summary

| ID | Module | Owner | Severity | Status |
|----|--------|-------|----------|--------|
| BUG-01 | budget.c | Kambala Victoria M.N | Low | FIXED |
| BUG-02 | reports.c / budget.h | Leena Kagola + Kambala Victoria | High | FIXED |
| BUG-03 | assets.c | Haundapiti Max.N | High | FIXED |

All bugs identified during testing have been resolved. The project now
compiles successfully into a working executable.

---

## BUG-01 — Incorrect & in scanf (FIXED)

- **File:** budget.c
- **Line:** 19
- **Owner:** Kambala Victoria M.N (225022133)
- **Severity:** Low (warning, not error)
- **Description:** The scanf call used the & operator on an array element
  that is already an address:
      scanf("%s", &departmentNames[budgetCount]);
  This produces a char (*)[50] type mismatch. The compiler emits a format
  warning.
- **Fix:**
      scanf("%s", departmentNames[budgetCount]);
- **Status:** FIXED — verified by recompilation. Warning gone.

---

## BUG-02 — reports.c Cannot Access Budget Variables (FIXED)

- **Files:** reports.c, budget.h
- **Lines:** 117, 127, 135 of reports.c
- **Owners:** Leena Kagola (225034123) + Kambala Victoria M.N (225022133)
- **Severity:** High (blocked compilation)
- **Description:** reports.c used four variables defined in budget.c but
  not visible from other files:
  - budgetCount
  - allocatedBudget[]
  - expenditure[]
  - departmentNames[][]

  Compiler error:
      reports.c:117: error: 'budgetCount' undeclared
      reports.c:127: error: 'allocatedBudget' undeclared
      reports.c:127: error: 'expenditure' undeclared
      reports.c:135: error: 'departmentNames' undeclared
- **Fix:**
  1. Added extern declarations to budget.h:
         extern char departmentNames[MAX_DEPARTMENTS][50];
         extern float allocatedBudget[MAX_DEPARTMENTS];
         extern float expenditure[MAX_DEPARTMENTS];
         extern int budgetCount;
  2. Added #include "budget.h" to the top of reports.c.
- **Status:** FIXED — verified by recompilation.

---

## BUG-03 — Missing assetMenu() Function (FIXED)

- **File:** assets.c
- **Owner:** Haundapiti Max.N (225147181)
- **Severity:** High (linker error, blocked the full build)
- **Description:** main.c called assetMenu(), declared in assets.h, but no
  definition of the function existed in assets.c. Full build failed with:
      undefined reference to `assetMenu'
- **Fix:** Added assetMenu() to assets.c following the pattern used by
  supplierMenu() in suppliers.c. The function presents a menu for adding,
  displaying and searching assets.
- **Status:** FIXED — verified by recompilation and linking.

---

## Testing Method

Each module compiled in isolation:

    gcc -std=c99 -Wall <module>.c -c -o <module>_test.o

Full build command:

    gcc -std=c99 -Wall main.c Employee.c budget.c suppliers.c assets.c reports.c -o mfms.exe

---

## Reporting Process

Bugs were reported to their respective owners via the group chat with:
- The exact file and line number
- The exact compiler error
- A suggested fix
- A request to push the fix to the repository

Each fix was re-tested after being pushed to confirm resolution.


