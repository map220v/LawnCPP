#if defined(_WIN32) && !defined(_DEBUG)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#ifdef __ANDROID__
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#endif

#include "LawnApp.h"
#include "Resources.h"
#include "todlib/TodStringFile.h"
using namespace Sexy;

bool (*gAppCloseRequest)();     //[0x69E6A0]
bool (*gAppHasUsedCheatKeys)(); //[0x69E6A4]
SexyString (*gGetCurrentLevelName)();

//volatile bool gDbgAttached = false;

// 0x44E8F0
int main(const int argc, char *argv[]) {
    //while (!gDbgAttached) sleep(1);
    TodStringListSetColors(gLawnStringFormats, gLawnStringFormatCount);
    gGetCurrentLevelName = LawnGetCurrentLevelName;
    gAppCloseRequest = LawnGetCloseRequest;
    gAppHasUsedCheatKeys = LawnHasUsedCheatKeys;
    gExtractResourcesByName = Sexy::ExtractResourcesByName;

#ifdef __ANDROID__
    const std::string aDataPath = SDL_GetAndroidExternalStoragePath();

    /*const std::string aDataPath = "/sdcard/PvZ";
    if (!SDL_AndroidRequestPermission("android.permission.READ_EXTERNAL_STORAGE"))
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "No permissions to read the external storage.", NULL);
        exit(-1);
    }
    std::filesystem::create_directory(aDataPath);*/

    SetAppDataFolder(aDataPath);
#endif

    TodLogger aTodLogger{};

    try {
        gLawnApp = new LawnApp();
#ifndef __ANDROID__
        auto shouldChangeDir =
            (!Sexy::FileExists("properties/resources.xml") && Sexy::FileExists("../properties/resources.xml")) ||
            (!Sexy::FileExists("main.pak") && Sexy::FileExists("../main.pak"));

        gLawnApp->mChangeDirTo = shouldChangeDir ? ".." : ".";
#else
        gLawnApp->mChangeDirTo = aDataPath;
#endif
        gLawnApp->DoParseCmdLine(argc, argv);
        gLawnApp->Init();
        gLawnApp->Start();
        gLawnApp->Shutdown();

        delete gLawnApp;
    }
    catch (std::runtime_error& aError)
    {
        LawnApp::HandleError(aError.what());
    }

    return 0;
};
