
#include "../common/utils.h"
#include "../Detours-main/src/detours.h"



bool g_didHooks = false;

void do_hooks()
{
    LOG("do_hooks");
    if (g_didHooks)
        return;
    g_didHooks = true;

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    attachCreateProcess();
    LONG error = DetourTransactionCommit();

    if (error == NO_ERROR) {
        LOG("did hook");
    }
    else {
        LOG("failed hook");
    }
}
