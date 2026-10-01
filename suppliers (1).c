/* ------------------------------------------------------------
 * suppliers.c - Supplier Management module (MFMS Project A)
 *
 * Features: add (with validation), display, search (ID / name /
 * town), compare two suppliers, and a supplier report.
 * ------------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "suppliers.h"

/* ---------- Storage ---------- */
char supplierID[MAX_SUPPLIERS][ID_LEN];
char supplierName[MAX_SUPPLIERS][NAME_LEN];
char supplierEmail[MAX_SUPPLIERS][EMAIL_LEN];
char supplierPhone[MAX_SUPPLIERS][PHONE_LEN];
char supplierTown[MAX_SUPPLIERS][TOWN_LEN];

int supplierCount = 0;

/* ---------- Private helper prototypes ---------- */
static void readNonBlank(const char *prompt, char *buf, int size);
static int  readInt(const char *prompt, int min, int max);
static int  isBlank(const char *s);
static void toLowerCopy(const char *src, char *dest, int size);
static int  isValidID(const char *id);
static int  isValidEmail(const char *email);
static int  isValidPhone(const char *phone);
static int  findByID(const char *id);
static int  nameExists(const char *name);
static void printSupplier(int i);
static void buildLabel(int i, char *out);
static void printTable(void);


/* ============================================================
 * INPUT HELPERS
 * ============================================================ */

/* Asks until the user types something that fits in buf and is not
 * empty/blank. Too-long input is rejected (and the extra characters
 * are flushed) so it never spills into the next prompt. */
static void readNonBlank(const char *prompt, char *buf, int size)
{
    size_t len;
    int ch;

    while (1) {
        printf("%s", prompt);
        if (fgets(buf, size, stdin) == NULL) {
            printf("\nInput closed. Exiting.\n");
            exit(0);
        }

        len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
        } else {
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            printf("Input too long (maximum %d characters).\n", size - 1);
            continue;
        }

        if (isBlank(buf)) {
            printf("Input cannot be empty.\n");
            continue;
        }
        return;
    }
}

/* Asks until the user enters a whole number between min and max */
static int readInt(const char *prompt, int min, int max)
{
    char line[16];
    char *end;
    long value;

    while (1) {
        readNonBlank(prompt, line, sizeof(line));

        value = strtol(line, &end, 10);
        while (isspace((unsigned char)*end))
            end++;

        if (*end != '\0') {
            printf("Please enter a whole number (no letters or symbols).\n");
            continue;
        }
        if (value < min || value > max) {
            printf("Please enter a number between %d and %d.\n", min, max);
            continue;
        }
        return (int)value;
    }
}

/* 1 if the string is empty or only spaces */
static int isBlank(const char *s)
{
    while (*s) {
        if (!isspace((unsigned char)*s))
            return 0;
        s++;
    }
    return 1;
}

/* Copies src to dest in lowercase (never writes more than size bytes) */
static void toLowerCopy(const char *src, char *dest, int size)
{
    int i;

    for (i = 0; src[i] != '\0' && i < size - 1; i++)
        dest[i] = (char)tolower((unsigned char)src[i]);
    dest[i] = '\0';
}


/* ============================================================
 * VALIDATION HELPERS
 * ============================================================ */

/* ID: 3 or more letters/digits, no spaces or symbols (e.g. SUP001) */
static int isValidID(const char *id)
{
    size_t i;

    if (strlen(id) < 3)
        return 0;
    for (i = 0; id[i] != '\0'; i++) {
        if (!isalnum((unsigned char)id[i]))
            return 0;
    }
    return 1;
}

/* Email: no spaces, one '@' with text before it, and a '.' after it
 * that is not the last character */
static int isValidEmail(const char *email)
{
    const char *at  = strchr(email, '@');
    const char *dot = strrchr(email, '.');

    if (strchr(email, ' ') != NULL)  return 0;
    if (at == NULL || at == email)   return 0;
    if (strchr(at + 1, '@') != NULL) return 0;
    if (dot == NULL || dot < at + 2) return 0;
    if (dot[1] == '\0')              return 0;
    return 1;
}

/* Phone: digits, spaces, '+' and '-' only, at least 7 digits */
static int isValidPhone(const char *phone)
{
    size_t i;
    int digits = 0;

    for (i = 0; i < strlen(phone); i++) {
        if (isdigit((unsigned char)phone[i]))
            digits++;
        else if (phone[i] != ' ' && phone[i] != '+' && phone[i] != '-')
            return 0;
    }
    return digits >= 7;
}

/* Index of the supplier with this ID (ignoring case), or -1 */
static int findByID(const char *id)
{
    int i;
    char a[ID_LEN], b[ID_LEN];

    toLowerCopy(id, a, ID_LEN);
    for (i = 0; i < supplierCount; i++) {
        toLowerCopy(supplierID[i], b, ID_LEN);
        if (strcmp(a, b) == 0)
            return i;
    }
    return -1;
}

/* 1 if a supplier with this name (ignoring case) already exists */
static int nameExists(const char *name)
{
    int i;
    char a[NAME_LEN], b[NAME_LEN];

    toLowerCopy(name, a, NAME_LEN);
    for (i = 0; i < supplierCount; i++) {
        toLowerCopy(supplierName[i], b, NAME_LEN);
        if (strcmp(a, b) == 0)
            return 1;
    }
    return 0;
}


/* ============================================================
 * OUTPUT HELPERS
 * ============================================================ */

static void printSupplier(int i)
{
    printf("  ID     : %s\n", supplierID[i]);
    printf("  Name   : %s\n", supplierName[i]);
    printf("  Email  : %s\n", supplierEmail[i]);
    printf("  Phone  : %s\n", supplierPhone[i]);
    printf("  Town   : %s\n", supplierTown[i]);
}

/* Builds "<ID> - <Name>" into out (out must hold ID_LEN + NAME_LEN + 4) */
static void buildLabel(int i, char *out)
{
    strcpy(out, supplierID[i]);
    strcat(out, " - ");
    strcat(out, supplierName[i]);
}

/* Prints all suppliers as a table (long text is cut to fit the columns) */
static void printTable(void)
{
    int i;

    printf("%-4s %-10s %-22s %-26s %-14s %-14s\n",
           "No.", "ID", "Name", "Email", "Phone", "Town");
    printf("------------------------------------------------------------"
           "-----------------------\n");
    for (i = 0; i < supplierCount; i++) {
        printf("%-4d %-10.10s %-22.22s %-26.26s %-14.14s %-14.14s\n",
               i + 1, supplierID[i], supplierName[i],
               supplierEmail[i], supplierPhone[i], supplierTown[i]);
    }
}


/* ============================================================
 * FEATURES
 * ============================================================ */

void addSupplier(void)
{
    char id[ID_LEN];
    char name[NAME_LEN];
    char email[EMAIL_LEN];
    char phone[PHONE_LEN];
    char town[TOWN_LEN];

    if (supplierCount >= MAX_SUPPLIERS) {
        printf("\nCannot add more suppliers. Maximum of %d reached.\n", MAX_SUPPLIERS);
        return;
    }

    printf("\n--- ADD NEW SUPPLIER (%d of %d) ---\n", supplierCount + 1, MAX_SUPPLIERS);

    /* ID: valid format and not already used */
    while (1) {
        readNonBlank("Enter Supplier ID (letters/digits, e.g. SUP001): ", id, ID_LEN);
        if (!isValidID(id)) {
            printf("Invalid ID. Use at least 3 letters/digits, no spaces or symbols.\n");
            continue;
        }
        if (findByID(id) != -1) {
            printf("That ID is already used by another supplier.\n");
            continue;
        }
        break;
    }

    /* Name: not empty, not already registered */
    while (1) {
        readNonBlank("Enter Supplier Name: ", name, NAME_LEN);
        if (nameExists(name)) {
            printf("A supplier with that name already exists.\n");
            continue;
        }
        break;
    }

    /* Email */
    while (1) {
        readNonBlank("Enter Email: ", email, EMAIL_LEN);
        if (!isValidEmail(email)) {
            printf("Invalid email. Example: sales@company.com\n");
            continue;
        }
        break;
    }

    /* Telephone */
    while (1) {
        readNonBlank("Enter Telephone Number: ", phone, PHONE_LEN);
        if (!isValidPhone(phone)) {
            printf("Invalid phone. Use digits, spaces, + or - (at least 7 digits).\n");
            continue;
        }
        break;
    }

    /* Town */
    readNonBlank("Enter Town/Location: ", town, TOWN_LEN);

    /* Everything valid -> store it */
    strcpy(supplierID[supplierCount],    id);
    strcpy(supplierName[supplierCount],  name);
    strcpy(supplierEmail[supplierCount], email);
    strcpy(supplierPhone[supplierCount], phone);
    strcpy(supplierTown[supplierCount],  town);
    supplierCount++;

    printf("\nSupplier added successfully!\n");
}

void displaySuppliers(void)
{
    if (supplierCount == 0) {
        printf("\nNo suppliers registered yet.\n");
        return;
    }

    printf("\n============================== SUPPLIER LIST "
           "==============================\n");
    printTable();
}

void searchSupplier(void)
{
    int choice, i, found = 0;
    char input[NAME_LEN];
    char target[NAME_LEN];
    char current[NAME_LEN];

    if (supplierCount == 0) {
        printf("\nNo suppliers to search.\n");
        return;
    }

    printf("\n--- SEARCH SUPPLIER ---\n");
    printf("1. By Supplier ID\n");
    printf("2. By Supplier Name\n");
    printf("3. By Town/Location\n");
    printf("4. Cancel\n");
    choice = readInt("Enter your choice: ", 1, 4);

    switch (choice) {
        case 1:
            readNonBlank("Enter Supplier ID: ", input, ID_LEN);
            i = findByID(input);
            if (i == -1) {
                printf("\nNo supplier with ID \"%s\" was found.\n", input);
            } else {
                printf("\n--- SUPPLIER FOUND ---\n");
                printSupplier(i);
            }
            break;

        case 2:
            readNonBlank("Enter Supplier Name: ", input, NAME_LEN);
            toLowerCopy(input, target, NAME_LEN);
            for (i = 0; i < supplierCount; i++) {
                toLowerCopy(supplierName[i], current, NAME_LEN);
                if (strcmp(current, target) == 0) {
                    printf("\n--- SUPPLIER FOUND ---\n");
                    printSupplier(i);
                    found = 1;
                    break;
                }
            }
            if (!found)
                printf("\nSupplier \"%s\" was not found.\n", input);
            break;

        case 3:
            readNonBlank("Enter Town/Location: ", input, TOWN_LEN);
            toLowerCopy(input, target, TOWN_LEN);
            for (i = 0; i < supplierCount; i++) {
                toLowerCopy(supplierTown[i], current, TOWN_LEN);
                if (strcmp(current, target) == 0) {
                    printf("\n--- SUPPLIER FOUND (record %d) ---\n", i + 1);
                    printSupplier(i);
                    found++;
                }
            }
            if (found == 0)
                printf("\nNo suppliers found in \"%s\".\n", input);
            else
                printf("\n%d supplier(s) found in that town.\n", found);
            break;

        default:
            printf("Search cancelled.\n");
    }
}

void compareSuppliers(void)
{
    char idA[ID_LEN], idB[ID_LEN];
    char labelA[ID_LEN + NAME_LEN + 4];
    char labelB[ID_LEN + NAME_LEN + 4];
    char townA[TOWN_LEN], townB[TOWN_LEN];
    int a, b;

    if (supplierCount < 2) {
        printf("\nYou need at least 2 suppliers to compare.\n");
        return;
    }

    printf("\n--- COMPARE SUPPLIERS ---\n");

    while (1) {
        readNonBlank("Enter first Supplier ID: ", idA, ID_LEN);
        a = findByID(idA);
        if (a == -1) {
            printf("No supplier with that ID.\n");
            continue;
        }
        break;
    }

    while (1) {
        readNonBlank("Enter second Supplier ID: ", idB, ID_LEN);
        b = findByID(idB);
        if (b == -1) {
            printf("No supplier with that ID.\n");
            continue;
        }
        if (b == a) {
            printf("Pick a different supplier to compare with.\n");
            continue;
        }
        break;
    }

    buildLabel(a, labelA);
    buildLabel(b, labelB);

    printf("\n%-8s | %-30.30s | %-30.30s\n", "", labelA, labelB);
    printf("---------+--------------------------------+-------------------------------\n");
    printf("%-8s | %-30.30s | %-30.30s\n", "ID",    supplierID[a],    supplierID[b]);
    printf("%-8s | %-30.30s | %-30.30s\n", "Name",  supplierName[a],  supplierName[b]);
    printf("%-8s | %-30.30s | %-30.30s\n", "Email", supplierEmail[a], supplierEmail[b]);
    printf("%-8s | %-30.30s | %-30.30s\n", "Phone", supplierPhone[a], supplierPhone[b]);
    printf("%-8s | %-30.30s | %-30.30s\n", "Town",  supplierTown[a],  supplierTown[b]);

    toLowerCopy(supplierTown[a], townA, TOWN_LEN);
    toLowerCopy(supplierTown[b], townB, TOWN_LEN);
    if (strcmp(townA, townB) == 0)
        printf("\nBoth suppliers operate in the same town.\n");
    else
        printf("\nThe suppliers operate in different towns.\n");
}

void displaySupplierReport(void)
{
    printf("\n=============== SUPPLIER REPORT ===============\n");
    printf("Total registered suppliers: %d\n", supplierCount);

    if (supplierCount == 0) {
        printf("No suppliers registered.\n");
        return;
    }

    printf("\n");
    printTable();
}


/* ============================================================
 * MENU
 * ============================================================ */

void supplierMenu(void)
{
    int choice;

    do {
        printf("\n========================================\n");
        printf("       SUPPLIER MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Compare Two Suppliers\n");
        printf("5. Supplier Report\n");
        printf("6. Back to Main Menu\n");

        choice = readInt("Enter your choice: ", 1, 6);

        switch (choice) {
            case 1: addSupplier();            break;
            case 2: displaySuppliers();       break;
            case 3: searchSupplier();         break;
            case 4: compareSuppliers();       break;
            case 5: displaySupplierReport();  break;
            case 6: printf("Returning to Main Menu...\n"); break;
        }
    } while (choice != 6);
}
