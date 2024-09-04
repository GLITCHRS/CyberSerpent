#ifndef CS_WINDOWS
#include "core/APILoader/Linux/LinuxAPILoader.h"

#include "pch/PCH.h"
#include <dlfcn.h>

bool LinuxAPILoader::load(const C_STR apiName)
{
    const char* charAPIName{ (const char*)apiName };
    m_API = dlopen(charAPIName, RTLD_LAZY);

    if (!m_API)
    {
        std::cerr << "Failed to load API\n";
        std::cerr << dlerror() << '\n';
        return false;
    }

    m_CreateShellFunc = (CreateShellFuncPtr)dlsym(m_API, "createShell");

    if (!m_CreateShellFunc)
    {
        std::cerr << "Failed to get function address (createShell)\n";
        std::cerr << dlerror() << '\n';
        return false;
    }

    return true;
}

void LinuxAPILoader::unload()
{
    if (m_API)
    {
        dlclose(m_API);
        m_API = nullptr;
        m_CreateShellFunc = nullptr;
    }
}

CS::Shell* LinuxAPILoader::CreateShell()
{
    if (m_CreateShellFunc)
        return m_CreateShellFunc();

    return nullptr;
}

LinuxAPILoader& LinuxAPILoader::Get()
{
    static LinuxAPILoader instance{};
    return instance;
}

#endif