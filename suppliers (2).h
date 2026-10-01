#ifndef SUPPLIERS_H
#define SUPPLIERS_H

/* ------------------------------------------------------------
 * suppliers.h - Supplier Management module (MFMS Project A)
 * ------------------------------------------------------------ */

#define MAX_SUPPLIERS 50
#define ID_LEN 20
#define NAME_LEN 50
#define EMAIL_LEN 50
#define PHONE_LEN 20
#define TOWN_LEN 50

/* Supplier data (parallel arrays: index i = one supplier).
 * Exposed with extern so other modules (e.g. Reports) can read them. */
extern char supplierID[MAX_SUPPLIERS][ID_LEN];
extern char supplierName[MAX_SUPPLIERS][NAME_LEN];
extern char supplierEmail[MAX_SUPPLIERS][EMAIL_LEN];
extern char supplierPhone[MAX_SUPPLIERS][PHONE_LEN];
extern char supplierTown[MAX_SUPPLIERS][TOWN_LEN];

extern int supplierCount;

void addSupplier(void);
void displaySuppliers(void);
void searchSupplier(void);
void compareSuppliers(void);
void displaySupplierReport(void);
void supplierMenu(void);

#endif
