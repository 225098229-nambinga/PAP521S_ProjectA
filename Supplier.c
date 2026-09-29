#include <stdio.h>
#include <string.h>


#define MAX_SUPPLIERS 5    
#define NAME_LEN      100
#define EMAIL_LEN     100
#define PHONE_LEN      30
#define TOWN_LEN       50


char supplierName [MAX_SUPPLIERS][NAME_LEN];
char supplierEmail[MAX_SUPPLIERS][EMAIL_LEN];
char supplierPhone[MAX_SUPPLIERS][PHONE_LEN];
char supplierTown [MAX_SUPPLIERS][TOWN_LEN];
int  supplierCount = 0;   


void displayMenu();
void addSupplier();
void displaySuppliers();
void searchSupplier();
void showNameLength();
void copySupplierName();
void buildDescription();
void removeNewline(char *str);


int main(void)
{
    int choice;

    do {
        displayMenu();
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');  
            printf("Invalid input.\n");
            continue;
        }
        getchar();

        switch (choice) {
            case 1: addSupplier();       break;
            case 2: displaySuppliers();  break;
            case 3: searchSupplier();    break;
            case 4: showNameLength();    break;
            case 5: copySupplierName();  break;
            case 6: buildDescription();  break;
            case 7: printf("Goodbye.\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
        printf("\n");

    } while (choice != 7);

    return 0;
}


void displayMenu()
{
    printf("===== SUPPLIER MANAGEMENT =====\n");
    printf(" 1. Add Supplier\n");
    printf(" 2. Display Suppliers\n");
    printf(" 3. Search Supplier\n");
    printf(" 4. Show Name Length\n");
    printf(" 5. Copy Supplier Name\n");
    printf(" 6. Build Supplier Description\n");
    printf(" 7. Exit\n");
    printf("===============================\n");
}


void addSupplier()
{
    if (supplierCount >= MAX_SUPPLIERS) {
        printf("Storage full. Maximum of %d suppliers reached.\n",
               MAX_SUPPLIERS);
        return;
    }

    printf("\n--- ADD SUPPLIER %d of %d ---\n",
           supplierCount + 1, MAX_SUPPLIERS);

    printf("Enter supplier name: ");
    fgets(supplierName[supplierCount], NAME_LEN, stdin);
    removeNewline(supplierName[supplierCount]);

    printf("Enter email: ");
    fgets(supplierEmail[supplierCount], EMAIL_LEN, stdin);
    removeNewline(supplierEmail[supplierCount]);

    printf("Enter phone: ");
    fgets(supplierPhone[supplierCount], PHONE_LEN, stdin);
    removeNewline(supplierPhone[supplierCount]);

    printf("Enter town: ");
    fgets(supplierTown[supplierCount], TOWN_LEN, stdin);
    removeNewline(supplierTown[supplierCount]);

    supplierCount++;
    printf("Supplier added successfully.\n");
}


void displaySuppliers()
{
    int i;
    if (supplierCount == 0) {
        printf("No suppliers have been added yet.\n");
        return;
    }

    printf("\n=========== SUPPLIER DETAILS ===========\n");
    for (i = 0; i < supplierCount; i++) {
        printf("\nSupplier #%d\n", i + 1);
        printf("Name : %s\n", supplierName[i]);
        printf("Email: %s\n", supplierEmail[i]);
        printf("Phone: %s\n", supplierPhone[i]);
        printf("Town : %s\n", supplierTown[i]);
    }
    printf("========================================\n");
}


void searchSupplier()
{
    char searchName[NAME_LEN];
    int i, found = 0;

    if (supplierCount == 0) {
        printf("No suppliers available to search.\n");
        return;
    }

    printf("Enter supplier name to search: ");
    fgets(searchName, NAME_LEN, stdin);
    removeNewline(searchName);

    for (i = 0; i < supplierCount; i++) {
        if (strcmp(supplierName[i], searchName) == 0) {
            printf("\nSupplier found at position %d.\n", i);
            printf("Name : %s\n", supplierName[i]);
            printf("Email: %s\n", supplierEmail[i]);
            printf("Phone: %s\n", supplierPhone[i]);
            printf("Town : %s\n", supplierTown[i]);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Supplier not found.\n");
}


void showNameLength()
{
    int i;
    if (supplierCount == 0) {
        printf("No suppliers have been added yet.\n");
        return;
    }

    printf("\n--- SUPPLIER NAME LENGTHS ---\n");
    for (i = 0; i < supplierCount; i++) {
        printf("Supplier #%d: %-30s -> length = %zu\n",
               i + 1,
               supplierName[i],
               strlen(supplierName[i]));
    }
}


void copySupplierName()
{
    int index;
    char backup[NAME_LEN];

    if (supplierCount == 0) {
        printf("No suppliers available to copy.\n");
        return;
    }

    printf("Enter supplier number to copy (1-%d): ", supplierCount);
    scanf("%d", &index);
    getchar();  /* consume newline */

    if (index < 1 || index > supplierCount) {
        printf("Invalid supplier number.\n");
        return;
    }

   
    strcpy(backup, supplierName[index - 1]);

    printf("\nOriginal name: %s\n", supplierName[index - 1]);
    printf("Backup copy  : %s\n", backup);
}


void buildDescription()
{
    int index;
    char description[250];

    if (supplierCount == 0) {
        printf("No suppliers available.\n");
        return;
    }

    printf("Enter supplier number (1-%d): ", supplierCount);
    scanf("%d", &index);
    getchar();

    if (index < 1 || index > supplierCount) {
        printf("Invalid supplier number.\n");
        return;
    }


    strcpy(description, supplierName[index - 1]);
    strcat(description, " operates in ");
    strcat(description, supplierTown[index - 1]);
    strcat(description, ".");

    printf("\nDescription: %s\n", description);
}


void removeNewline(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}