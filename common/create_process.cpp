#include "../common/utils.h"

#include "../Detours-main/src/detours.h"



typedef int (WINAPI* MessageBoxW_ptr)(HWND, LPCWSTR, LPCWSTR, UINT);

typedef BOOL(WINAPI* CreateProcessW_ptr)(
    LPCWSTR, // lpApplicationName
    LPWSTR,  // lpCommandLine
    LPSECURITY_ATTRIBUTES, // lpProcessAttributes,
    LPSECURITY_ATTRIBUTES, // lpThreadAttributes,
    BOOL,   //                  bInheritHandles,
    DWORD,  //               dwCreationFlags,
    LPVOID,  //              lpEnvironment,
    LPCWSTR, //              lpCurrentDirectory,
    LPSTARTUPINFOW, //        lpStartupInfo,
    LPPROCESS_INFORMATION  // lpProcessInformation
    );

// Pointer for calling original MessageBoxW.
CreateProcessW_ptr fpCreateProcessW = nullptr;



BOOL  WINAPI detour_CreateProcessW(LPCWSTR               lpApplicationName,
                                   LPWSTR                lpCommandLine,
                                   LPSECURITY_ATTRIBUTES lpProcessAttributes,
                                   LPSECURITY_ATTRIBUTES lpThreadAttributes,
                                   BOOL                  bInheritHandles,
                                   DWORD                 dwCreationFlags,
                                   LPVOID                lpEnvironment,
                                   LPCWSTR               lpCurrentDirectory,
                                   LPSTARTUPINFOW        lpStartupInfo,
                                   LPPROCESS_INFORMATION lpProcessInformation)
{
    const wchar_t* name = lpCommandLine;
    if (name == nullptr)
        name = lpApplicationName;
    if (name == nullptr)
        name = L"[NULL]";
    LOGW(L"call CreateProcessW: " << name);

    bool doInject = false;

    std::wstring wname(name);
    if (str_contains(wname, L"MSBuild.exe"))
    {
        doInject = true;
    }

    if (doInject)
    {
        const char injDll[] = "C:\\Projects\\madhim_build\\x64\\Debug\\inject_dll64.dll";
        const char* rlpDlls[] = { injDll };


        return DetourCreateProcessWithDllsW(
            lpApplicationName,
            lpCommandLine,
            lpProcessAttributes,
            lpThreadAttributes,
            bInheritHandles,
            dwCreationFlags,
            lpEnvironment,
            lpCurrentDirectory,
            lpStartupInfo,
            lpProcessInformation,
            1,
            rlpDlls,
            fpCreateProcessW);

    }
    else
    {
        return fpCreateProcessW(
            lpApplicationName,
            lpCommandLine,
            lpProcessAttributes,
            lpThreadAttributes,
            bInheritHandles,
            dwCreationFlags,
            lpEnvironment,
            lpCurrentDirectory,
            lpStartupInfo,
            lpProcessInformation);
    }
}


void attachCreateProcess()
{
    fpCreateProcessW = CreateProcessW;
    DetourAttach(&(PVOID&)fpCreateProcessW, detour_CreateProcessW);
}

void detachCreateProcess()
{
    DetourDetach(&(PVOID&)fpCreateProcessW, detour_CreateProcessW);
}