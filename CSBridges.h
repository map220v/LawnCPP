#pragma once
#include "SexyAppFramework/Image.h"
class SM_SeedType;

void RightWinPressed();

template <typename enumName> class SmartEnum
{
public:
    char* theName;
    int    theValue;
};

struct Vector2
{
    int x, y;
};

class PlantDefinition
{
public:
    SmartEnum<SM_SeedType> mSeedType;        //+0x0
Sexy::Image** mPlantImage;        //+0x4
    enum ReanimationType         mReanimationType;   //+0x8
    int                     mPacketIndex;       //+0xC
    int                     mSeedCost;          //+0x10
    int                     mRefreshTime;       //+0x14
    enum PlantSubClass           mSubClass;          //+0x18
    int                     mLaunchRate;        //+0x1C
    const SexyChar* mPlantName;         //+0x20
    enum PlantFamily
    {
        NONE,
        PEASHOOTER,
    };
    PlantFamily mFamily;
};
class Functions
{
public:
    static HMODULE lastLoadedCore;
    static void(__cdecl * gRegisterMethod)(char* theName, void* theFunction);
    static void* (__cdecl * gGetCSFunctionByName)(char* theName);
    static PlantDefinition&(__cdecl * gPlantDefinition)(int theIndex);
    static void(__cdecl* WinMain_Hook)(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int mCmdShow);
    static void(__cdecl* Reload)();
    static int(__cdecl* getSeedTypes)(bool includeUnusable);
};
class GlobalPlantDefinitions
{
public:
	PlantDefinition& operator [](int index);
};

extern GlobalPlantDefinitions gPlantDefs;



