#include "../common/utils.h"
#include "../Detours-main/src/detours.h"

// reference
// https://github.com/microsoft/Detours/wiki/Reference
// dll example
// https://github.com/microsoft/Detours/blob/main/samples/withdll/withdll.cpp
// simple hook example
// https://github.com/microsoft/Detours/blob/main/samples/simple/simple.cpp



int main()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    attachCreateProcess();
    LONG error = DetourTransactionCommit();

    if (error == NO_ERROR) {
        LOG_C("did hook");
    }
    else {
        LOG_C("failed hook");
    }


    STARTUPINFOW si = { 0 };
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi = { 0 };
    wchar_t cmd[] = L"calc.exe";
    BOOL ret = CreateProcessW(nullptr, cmd, nullptr, nullptr, false, 0, nullptr, nullptr, &si, &pi);
    if (!ret)
    {
        LOG_C("failed CreateProcess");
    }


    return 0;
}

