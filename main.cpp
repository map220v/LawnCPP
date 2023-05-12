#include "CSBridges.h"
#include "LawnApp.h"
#include "Resources.h"
#include "Sexy.TodLib/TodStringFile.h"
#include <iostream>
#include "Lawn/Plant.h"
#include "Lawn/Projectile.h"
#include "Lawn/Board.h"
using namespace Sexy;

bool (*gAppCloseRequest)();				//[0x69E6A0]
bool (*gAppHasUsedCheatKeys)();			//[0x69E6A4]
SexyString (*gGetCurrentLevelName)();
GlobalPlantDefinitions gPlantDefs =  GlobalPlantDefinitions();

void hello()
{
	std::cout << "Hello" << std::endl;
}

 void(__cdecl* Functions::gRegisterMethod)(char* theName, void* theFunction);
 void* (__cdecl* Functions::gGetCSFunctionByName)(char* theName);
PlantDefinition& (__cdecl* Functions::gPlantDefinition)(int theIndex);
void(__cdecl* Functions::WinMain_Hook)(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int mCmdShow);
 void(__cdecl* Functions::Reload)();
 int(__cdecl* Functions::getSeedTypes)(bool includeUnusable);
 HMODULE lastLoadedCore;
void RightWinPressed()
{
	//LoadCore(); i tried doing it this way but no luck, alas
	Functions::Reload();
}

void PlayFoleyStatic(LawnApp* theApp,FoleyType theFoleyType)
{
	theApp->PlayFoley(theFoleyType);
}

Projectile* AddProjectileStatic(Board* theBoard,int theX, int theY, int theRenderOrder, int theRow, ProjectileType theProjectileType)
{
	return theBoard->AddProjectile(theX, theY, theRenderOrder, theRow, theProjectileType);
}

int GetDamageRangeFlagsStatic(Plant* thePlant,PlantWeapon thePlantWeapon)
{
	return thePlant->GetDamageRangeFlags(thePlantWeapon);
}
void DoRowAreaDamageStatic(Plant* thePlant, int theDamage, unsigned int theDamageFlags)
{
	thePlant->DoRowAreaDamage(theDamage, theDamageFlags);
}
Coin* AddCoinStatic(Board* theBoard,int theX, int theY, CoinType theCoinType, CoinMotion theCoinMotion)
{
	return theBoard->AddCoin(theX, theY, theCoinType, theCoinMotion);
}

Reanimation* ReanimationTryToGetStatic(LawnApp* theApp,ReanimationID theReanimationID)
{
	return theApp->ReanimationTryToGet(theReanimationID);
}

void PlayBodyReanimStatic(Plant* thePlant,const char* theTrackName, ReanimLoopType theLoopType, int theBlendTime, float theAnimRate)
{
	thePlant->PlayBodyReanim(theTrackName, theLoopType, theBlendTime, theAnimRate);
}
Zombie* FindSquashTargetStatic(Plant* thePlant)
{
	return thePlant->FindSquashTarget();
}
ZombieID ZombieGetIDStatic(Board* theBoard,Zombie* theZombie)
{
	return theBoard->ZombieGetID(theZombie);
}
float ZombieTargetLeadXStatic(Zombie* theZombie,float theTime)
{
	return theZombie->ZombieTargetLeadX(theTime);
}

int PixelToGridXKeepOnBoardStatic(Board* theBoard,int theX, int theY)
{
	return theBoard->PixelToGridXKeepOnBoard(theX,theY);
}

int GridToPixelYStatic(Board* theBoard,int theGridX, int theGridY)
{
	return theBoard->GridToPixelY(theGridX, theGridY);
}
int GridToPixelXStatic(Board* theBoard, int theGridX, int theGridY)
{
	return theBoard->GridToPixelX(theGridX, theGridY);
}
void DoSquashDamageStatic(Plant* thePlant)
{
	thePlant->DoSquashDamage();
}
bool IsPoolSquareStatic(Board* theBoard,int theGridX, int theGridY)
{
	return theBoard->IsPoolSquare(theGridX, theGridY);
}

//0x44E8F0
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//gHInstance = hInstance;
	AllocConsole(); 
	FILE* fDummy;
	freopen_s(&fDummy, "CONIN$", "r", stdin);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);
	freopen_s(&fDummy, "CONOUT$", "w", stdout);
	 lastLoadedCore = LoadLibrary("PVZMECSMainCore.dll");
	if (lastLoadedCore == nullptr)return 0;
	Functions::gRegisterMethod = (void(__cdecl*)(char* theName, void* theFunction))GetProcAddress(lastLoadedCore, "RegisterMethod");
	Functions::gGetCSFunctionByName = (void* (__cdecl*)(char* theName))GetProcAddress(lastLoadedCore, "GetCSFunctionByName");
	Functions::Reload = (void(__cdecl*)())GetProcAddress(lastLoadedCore, "Reload");
	Functions::gRegisterMethod("hello", hello);
	Functions::gRegisterMethod("PlayFoley", PlayFoleyStatic);
	Functions::gRegisterMethod("AddProjectile", AddProjectileStatic);
	Functions::gRegisterMethod("GetDamageRangeFlags", GetDamageRangeFlagsStatic);
	Functions::gRegisterMethod("DoRowAreaDamage", DoRowAreaDamageStatic);
	Functions::gRegisterMethod("AddCoin", AddCoinStatic);
	Functions::gRegisterMethod("ReanimationTryToGet", ReanimationTryToGetStatic);
	Functions::gRegisterMethod("PlayBodyReanim", PlayBodyReanimStatic);
	Functions::gRegisterMethod("FindSquashTarget", FindSquashTargetStatic);
	Functions::gRegisterMethod("ZombieGetID", ZombieGetIDStatic);
	Functions::gRegisterMethod("ZombieTargetLeadX", ZombieTargetLeadXStatic);
	Functions::gRegisterMethod("PixelToGridXKeepOnBoard", PixelToGridXKeepOnBoardStatic);
	Functions::gRegisterMethod("GridToPixelY", GridToPixelYStatic);
	Functions::gRegisterMethod("GridToPixelX", GridToPixelXStatic);
	Functions::gRegisterMethod("TodAnimateCurve", TodAnimateCurve);
	Functions::gRegisterMethod("DoSquashDamage", DoSquashDamageStatic);
	Functions::gRegisterMethod("IsPoolSquare", IsPoolSquareStatic);
	Functions::gPlantDefinition = (PlantDefinition & (__cdecl*)(int theIndex))GetProcAddress(lastLoadedCore, "getPlantDefinition");
	Functions::WinMain_Hook = (void(__cdecl*)(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int mCmdShow)) GetProcAddress(lastLoadedCore, "WinMain");
	Functions::WinMain_Hook(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	Functions::getSeedTypes = (int(__cdecl*)(bool includeUnusable))GetProcAddress(lastLoadedCore, "NUM_SEED_TYPES");
	std::cout << "Plants added " <<NUM_SEED_TYPES << std::endl;

	//auto testDef = (PlantDefinition(__cdecl*)())GetProcAddress(lib, "getPlantDefinitionTest");
	PlantDefinition def = gPlantDefs[1];
	std::cout << def.mSeedType.theValue<<"  " << def.mSeedType.theValue << "   " << def.mPlantName << std::endl;
	((void(__stdcall*)())Functions::gGetCSFunctionByName("PVZMECSMainCore.Main.CSharpHello"))();
	TodStringListSetColors(gLawnStringFormats, gLawnStringFormatCount);
	gGetCurrentLevelName = LawnGetCurrentLevelName;
	gAppCloseRequest = LawnGetCloseRequest;
	gAppHasUsedCheatKeys = LawnHasUsedCheatKeys;
	gExtractResourcesByName = Sexy::ExtractResourcesByName;
	
	gLawnApp = new LawnApp();
	gLawnApp->mChangeDirTo = (!Sexy::FileExists("properties\\resources.xml") && Sexy::FileExists("..\\properties\\resources.xml")) ? ".." : ".";
	
	gLawnApp->Init();
	gLawnApp->Start();

	gLawnApp->Shutdown();
	if (gLawnApp)
		delete gLawnApp;

	return 0;
};