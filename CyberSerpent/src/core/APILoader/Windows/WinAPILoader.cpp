#ifdef CS_WINDOWS

#include <iostream>
#include "core/APILoader/Windows/WinAPILoader.h"


bool WinAPILoader::load(const wchar_t* apiName)
{
    m_API = LoadLibraryW(apiName);

    if (!m_API)
    {
        std::cerr << "Failed to load API\n";
        std::cerr << GetLastError() << '\n';
        return false;
    }

    m_CreateShell = (CreateShellFunc)GetProcAddress(m_API, "createShell");

    if (!m_CreateShell)
    {
        std::cerr << "Failed to get function address (createShell)\n";
        std::cerr << GetLastError() << '\n';
        return false;
    }

    return true;
}

void WinAPILoader::unload()
{
    if (m_API)
    {
        FreeLibrary(m_API);
        m_API = nullptr;
        m_CreateShell = nullptr;
    }
}

CS::Shell* WinAPILoader::CreateShell()
{
    if (m_CreateShell)
        return m_CreateShell();

    return nullptr;
}

WinAPILoader& WinAPILoader::Get()
{
    static WinAPILoader instance{};
    return instance;
}

#endif