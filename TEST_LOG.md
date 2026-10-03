# TEST LOG — Municipal Financial Management System (PAP521S Project A)

**Tester:** Nambinga Mwene Etuhole (225098229)
**Role:** Testing, Documentation and Git Coordination
**Date:** 3 October 2026
**Environment:** Windows, GCC (MinGW), VS Code

---

## 1. Purpose

This document records the results of compilation and functional testing
performed on each module of the Municipal Financial Management System (MFMS)
before submission of Project A.

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
| 4 | assets.c | Haundapiti Max.N | PASS | No errors or warnings |
| 5 | reports.c | Leena Kagola | FAIL | Cannot see budget variables (Bug 2) |
| 6 | main.c | Esra-Gandja Shigwedha | PASS | No errors or warnings |
| 7 | Full project | All members | FAIL | Blocked by reports.c |

---

## 3. Bugs Identified and Reported

### BUG-01 — budget.c Line 19 (FIXED)
- **Owner:** Kambala Victoria M.N
- **Issue:** scanf used unnecessary & on an array element
- **Fix:** Removed the &
- **Status:** Fixed and verified

### BUG-02 — reports.c Cannot Access Budget Variables (OPEN)
- **Owners:** Leena Kagola + Kambala Victoria M.N
- **Issue:** reports.c uses budgetCount, allocatedBudget[], expenditure[],
  departmentNames[][] which are only defined in budget.c
- **Fix:** Declare these as extern in budget.h and include it in reports.c
- **Status:** Reported, awaiting fix

### BUG-03 — assets.c Missing assetMenu() (OPEN)
- **Owner:** Haundapiti Max.N
- **Issue:** main.c calls assetMenu() but assets.c does not define it
- **Fix:** Add assetMenu() function to assets.c
- **Status:** Reported, awaiting fix

---

## 4. Functional Test Plan (After Build Succeeds)

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

- 4 of 5 modules compile cleanly
- 1 warning fixed after being reported (Bug 1)
- 2 bugs remain open (Bug 2, Bug 3)
- Full build and functional testing pending until Bugs 2 and 3 are resolved

---

*End of Test Log.*