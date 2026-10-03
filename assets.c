#include <stdio.h>
#include <string.h>
#include "assets.h"

Asset assets[MAX_ASSETS];

int assetCount = 0;


void addAsset()
{
    if (assetCount >= MAX_ASSETS)
    {
        printf("\nAsset register is full!\n");
        return;
    }

    printf("\n===== ADD ASSET =====\n");

    printf("Enter Asset ID: ");
    scanf("%d", &assets[assetCount].assetID);
    getchar();

    printf("Enter Asset Name: ");
    fgets(assets[assetCount].assetName,
          sizeof(assets[assetCount].assetName), stdin);

    assets[assetCount].assetName[
        strcspn(assets[assetCount].assetName, "\n")
    ] = '\0';


    printf("Enter Asset Type: ");
    fgets(assets[assetCount].assetType,
          sizeof(assets[assetCount].assetType), stdin);

    assets[assetCount].assetType[
        strcspn(assets[assetCount].assetType, "\n")
    ] = '\0';


    printf("Enter Purchase Value: N$ ");
    scanf("%f", &assets[assetCount].purchaseValue);
    getchar();


    printf("Enter Department: ");
    fgets(assets[assetCount].department,
          sizeof(assets[assetCount].department), stdin);

    assets[assetCount].department[
        strcspn(assets[assetCount].department, "\n")
    ] = '\0';


    printf("Enter Condition: ");
    fgets(assets[assetCount].condition,
          sizeof(assets[assetCount].condition), stdin);

    assets[assetCount].condition[
        strcspn(assets[assetCount].condition, "\n")
    ] = '\0';


    assetCount++;

    printf("\nAsset added successfully!\n");
}


void displayAssets()
{
    if (assetCount == 0)
    {
        printf("\nNo assets registered.\n");
        return;
    }

    printf("\n========== ASSET REGISTER ==========\n");

    for (int i = 0; i < assetCount; i++)
    {
        printf("\nAsset %d\n", i + 1);
        printf("Asset ID       : %d\n", assets[i].assetID);
        printf("Asset Name     : %s\n", assets[i].assetName);
        printf("Asset Type     : %s\n", assets[i].assetType);
        printf("Purchase Value : N$ %.2f\n", assets[i].purchaseValue);
        printf("Department     : %s\n", assets[i].department);
        printf("Condition      : %s\n", assets[i].condition);
    }

    printf("\n====================================\n");
}

void searchAsset()
{
    int id;
    int found = 0;

    printf("\n===== SEARCH ASSET =====\n");

    printf("Enter Asset ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < assetCount; i++)
    {
        if (assets[i].assetID == id)
        {
            printf("\nAsset Found!\n");
            printf("Asset ID       : %d\n", assets[i].assetID);
            printf("Asset Name     : %s\n", assets[i].assetName);
            printf("Asset Type     : %s\n", assets[i].assetType);
            printf("Purchase Value : N$ %.2f\n", assets[i].purchaseValue);
            printf("Department     : %s\n", assets[i].department);
            printf("Condition      : %s\n", assets[i].condition);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nAsset with ID %d was not found.\n", id);
    }
}

void assetMenu(void)
{
    int choice;

    do {
        printf("\n========================================\n");
        printf("         ASSET MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset\n");
        printf("0. Back to Main Menu\n");
        printf("Choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1: addAsset();      break;
            case 2: displayAssets(); break;
            case 3: searchAsset();   break;
            case 0: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
}


