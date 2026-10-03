# TEST LOG — Municipal Financial Management System (PAP521S Project A)

**Tester:** Nambinga Mwene Etuhole (225098229)
**Role:** Testing, Documentation and Git Coordination
**Date:** 3 October 2026
**Environment:** Windows, GCC (MinGW), VS Code

---

## 1. Purpose

This document records the results of compilation and integration testing
performed on the Municipal Financial Management System (MFMS) before
submission of Project A.

Each module was compiled individually using the command:

    gcc -std=c99 -Wall <module>.c -c -o <module>_test.o

This isolates each module and identifies which files compile cleanly and
which contain errors that must be fixed before the project can be built.

---

## 2. Compilation Test Results

| # | Module | Owner | Result | Notes |
|---|--------|-------|--------|-------|
| 1 | suppliers.c | Paulina Gabriel | PASS | No errors or warnings |
| 2 | Employee.c | Lita Oiva Mekondjo | PASS | No errors or warnings |
| 3 | budget.c | Kambala Victoria M.N | FIXED | Line 19 scanf had extra &; corrected |
| 4 | assets.c | Haundapiti Max.N | FIXED | assetMenu() added; compiles cleanly |
| 5 | reports.c | Leena Kagola | FIXED | Now sees budget variables via budget.h |
| 6 | main.c | Esra-Gandja Shigwedha | PASS | No errors or warnings |
| 7 | Full project | All members | PASS | mfms.exe produced successfully |

---

## 3. Bugs Identified and Reported

### BUG-01 — budget.c Line 19 (FIXED)
- **Owner:** Kambala Victoria M.N
- **Issue:** scanf used unnecessary & on an array element
- **Fix:** Removed the &
- **Status:** Fixed and verified

### BUG-02 — reports.c Cannot Access Budget Variables (FIXED)
- **Owners:** Leena Kagola + Kambala Victoria M.N
- **Issue:** reports.c used budgetCount, allocatedBudget[], expenditure[],
  departmentNames[][] which were only defined in budget.c
- **Fix:** Added extern declarations to budget.h and included it in reports.c
- **Status:** Fixed and verified

### BUG-03 — assets.c Missing assetMenu() (FIXED)
- **Owner:** Haundapiti Max.N
- **Issue:** main.c called assetMenu() but assets.c did not define it
- **Fix:** Added assetMenu() function to assets.c
- **Status:** Fixed and verified

---

## 4. Functional Test Plan

| # | Menu Option | Test Case | Expected Result |
|---|-------------|-----------|-----------------|
| 1 | Employee | Add employee | Employee saved |
| 2 | Employee | Search employee | Employee found |
| 3 | Budget | Add budget | Budget saved |
| 4 | Budget | Negative value | Rejected |
| 5 | Supplier | Add supplier | Supplier saved |
| 6 | Supplier | Invalid email | Rejected |
| 7 | Supplier | Search by name | Found |
| 8 | Asset | Add asset | Asset saved |
| 9 | Reports | All 4 reports | Display correctly |
| 10 | Main Menu | Invalid option | Error message |
| 11 | Main Menu | Exit | Clean exit |

---

## 5. Summary

- 6 of 6 modules compile cleanly
- All 3 identified bugs have been fixed and verified
- The full project compiles successfully into mfms.exe
- Functional testing is ready to be performed
