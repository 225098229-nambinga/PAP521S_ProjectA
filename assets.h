#ifndef ASSET_H
#define ASSET_H

#define MAX_ASSETS 50

typedef struct {
	int assetID;
	char assetName[50];
	char assetType[30];
	float purchaseValue;
	char department[50];
	char condition[30];
} Asset;

extern Asset assets[MAX_ASSETS];
extern int assetCount;

// Function prototypes 
void assetMenu(void);
void addAsset(void);
void displayAssets(void);
void searchAsset(void);
int findAsset(int id);

#endif