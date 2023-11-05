#pragma once
#include <string>
#include <iostream>
#include <sstream>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define LOG_C(...) do { std::cout << __VA_ARGS__ << std::endl; } while(false)
#define LOG(...) do { std::stringstream ss; ss << __VA_ARGS__ << "\n"; OutputDebugStringA(ss.str().c_str()); } while(false)
#define LOGW(...) do { std::wstringstream ss; ss << __VA_ARGS__ << L"\n"; OutputDebugStringW(ss.str().c_str()); } while(false)



inline bool str_contains(const std::wstring & base, const std::wstring & search_what)
{
    auto it = base.find(search_what);
    return (it != std::wstring::npos);
}

void attachCreateProcess();
void detachCreateProcess();