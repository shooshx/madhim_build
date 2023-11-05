
#include "../common/utils.h"

#include "../Detours-main/src/detours.h"



BOOL APIENTRY DllMain(HMODULE hModule, DWORD  dwReason, LPVOID lpReserved)
{
    LONG error;

    if (DetourIsHelperProcess()) {
        return TRUE;
    }

    if (dwReason == DLL_PROCESS_ATTACH) {
        DetourRestoreAfterWith();

        char name[256] = { 0 };
        GetModuleFileNameA(nullptr, name, 255);
        LOG("running hooks in `" << name << "`");

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        attachCreateProcess();
        error = DetourTransactionCommit();

        if (error == NO_ERROR) {
            LOG("Hooks succeeded");
        }
        else {
            LOG("Hooks failed " << error);
        }
    }
    else if (dwReason == DLL_PROCESS_DETACH) {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        detachCreateProcess();
        error = DetourTransactionCommit();
        LOG("Removed hooks");
    }
    return TRUE;
}

