#ifndef ASSET_H
#define ASSET_H

#define MAX_ASSET 50

/* Parallel arrays */
extern char  assetID[MAX_ASSET][20];
extern char  assetName[MAX_ASSET][50];
extern char  assetType[MAX_ASSET][30];
extern float assetValue[MAX_ASSET];
extern char  assetDept[MAX_ASSET][50];
extern char  assetCondition[MAX_ASSET][30];
extern int   assetCount;

/* Function prototypes */
void assetMenu(void);
void addAsset(void);
void displayAssets(void);
void searchAsset(void);
int  findAsset(char id[]);

#endif