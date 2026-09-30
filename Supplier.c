#include <stdio.h>
#include <string.h>
#include "supplier.h"

char supplierID[MAX_SUPPLIERS][ID_LEN];
char supplierName[MAX_SUPPLIERS][NAME_LEN];
char email[MAX_SUPPLIERS][EMAIL_LEN];
char phone[MAX_SUPPLIERS][PHONE_LEN];
char town[MAX_SUPPLIERS][TOWN_LEN];

int supplierCount = 0;

static void removeNewline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

void addSupplier(void) {
    if (supplierCount >= MAX_SUPPLIERS) {
        printf("\nCannot add more suppliers. Maximum of %d reached.\n", MAX_SUPPLIERS);
        return;
    }

    printf("\n--- ADD NEW SUPPLIER ---\n");

    printf("Enter Supplier ID: ");
    fgets(supplierID[supplierCount], ID_LEN, stdin);
    removeNewline(supplierID[supplierCount]);

    printf("Enter Supplier Name: ");
    fgets(supplierName[supplierCount], NAME_LEN, stdin);
    removeNewline(supplierName[supplierCount]);

    printf("Enter Email: ");
    fgets(email[supplierCount], EMAIL_LEN, stdin);
    removeNewline(email[supplierCount]);

    printf("Enter Telephone Number: ");
    fgets(phone[supplierCount], PHONE_LEN, stdin);
    removeNewline(phone[supplierCount]);

    printf("Enter Town/Location: ");
    fgets(town[supplierCount], TOWN_LEN, stdin);
    removeNewline(town[supplierCount]);

    supplierCount++;
    printf("\nSupplier added successfully!\n");
}
void displaySuppliers(void) {
    if (supplierCount == 0) {
        printf("\nNo suppliers registered yet.\n");
        return;
    }

    printf("\n==================== SUPPLIER LIST ====================\n");
    for (int i = 0; i < supplierCount; i++) {
        printf("\nSupplier #%d\n", i + 1);
        printf("  ID     : %s\n", supplierID[i]);
        printf("  Name   : %s\n", supplierName[i]);
        printf("  Email  : %s\n", email[i]);
        printf("  Phone  : %s\n", phone[i]);
        printf("  Town   : %s\n", town[i]);
    }
    printf("=======================================================\n");
}

void searchSupplier(void) {
    char searchKey[NAME_LEN];
    int found = 0;

    if (supplierCount == 0) {
        printf("\nNo suppliers to search.\n");
        return;
    }

    printf("\nEnter Supplier Name or ID to search: ");
    fgets(searchKey, NAME_LEN, stdin);
    removeNewline(searchKey);

    for (int i = 0; i < supplierCount; i++) {
        if (strcmp(supplierName[i], searchKey) == 0 ||
            strcmp(supplierID[i], searchKey) == 0) {

            printf("\n--- SUPPLIER FOUND ---\n");
            printf("ID     : %s\n", supplierID[i]);
            printf("Name   : %s\n", supplierName[i]);
            printf("Email  : %s\n", email[i]);
            printf("Phone  : %s\n", phone[i]);
            printf("Town   : %s\n", town[i]);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nSupplier \"%s\" was not found.\n", searchKey);
    }
}

void supplierMenu(void) {
    int choice;

    do {
        printf("\n========================================\n");
        printf("       SUPPLIER MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();          

        switch (choice) {
            case 1:
                addSupplier();
                break;
            case 2:
                displaySuppliers();
                break;
            case 3:
                searchSupplier();
                break;
            case 4:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}

