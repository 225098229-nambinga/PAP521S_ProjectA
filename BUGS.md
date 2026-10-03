# BUG TRACKING LOG — MFMS Project A

**Coordinator:** Nambinga Mwene Etuhole (225098229)
**Role:** Testing, Documentation and Git Coordination
**Date:** 3 October 2026

---

## Summary

| ID | Module | Owner | Severity | Status |
|----|--------|-------|----------|--------|
| BUG-01 | budget.c | Kambala Victoria M.N | Low | FIXED |
| BUG-02 | reports.c / budget.h | Leena Kagola + Kambala Victoria | High | OPEN |
| BUG-03 | assets.c | Haundapiti Max.N | High | OPEN |

---

## BUG-01 - Incorrect & in scanf (FIXED)

- File: budget.c
- Line: 19
- Owner: Kambala Victoria M.N (225022133)
- Severity: Low (warning)
- Description: Extra & used on an array element.
- Original: scanf("%s", &departmentNames[budgetCount]);
- Fix: scanf("%s", departmentNames[budgetCount]);
- Status: Fixed by owner and re-tested. Warning gone.

---

## BUG-02 - reports.c Cannot Access Budget Variables (OPEN)

- Files: reports.c, budget.h
- Lines: 117, 127, 135 of reports.c
- Owners: Leena Kagola + Kambala Victoria M.N
- Severity: High (blocks compilation)
- Description: reports.c uses budgetCount, allocatedBudget[],
  expenditure[], departmentNames[][] which are only declared in budget.c.
- Fix required:
  1. Add extern declarations of these variables to budget.h.
  2. Add #include "budget.h" at the top of reports.c.
- Status: Reported, awaiting fix.

---

## BUG-03 - Missing assetMenu() Function (OPEN)

- File: assets.c
- Owner: Haundapiti Max.N (225147181)
- Severity: High (linker error)
- Description: main.c calls assetMenu(), declared in assets.h,
  but not defined in assets.c. Full build fails with:
  undefined reference to 'assetMenu'.
- Fix required: Add an assetMenu() function to assets.c, following
  the pattern used by supplierMenu() in suppliers.c.
- Status: Reported, awaiting fix.

---

## Testing Method

Each module compiled in isolation:

    gcc -std=c99 -Wall <module>.c -c -o <module>_test.o

Full build command:

    gcc -std=c99 -Wall main.c Employee.c budget.c suppliers.c assets.c reports.c -o mfms.exe

---

*End of Bug Tracking Log.*