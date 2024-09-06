#ifndef CS_WINDOWS

#include "system/linux/Linux.h"

#include "pch/pch.h"
#include "system/Command.h"
#include <unistd.h>
#include <dlfcn.h>

static std::string FileToString(FILE* file)
{
	std::string result;
	char buffer[128];

	while (fgets(buffer, sizeof(buffer), file) != nullptr)
		result += buffer;

	return result;
}

std::string Linux::ExecCommands(const std::string& command) const
{
	std::string commandResult{ "" };
	Command sysCommand{ m_SysCommands.at(command) };
	FILE* pipe = popen(sysCommand.command.c_str(), sysCommand.mode.c_str());

	if (sysCommand.mode == "w")
	{
		commandResult = FileToString(pipe);
	}

	if (pipe)
		pclose(pipe);

	return commandResult;
}

bool Linux::IsRoot() const
{
	return getuid() == 0;
}

bool Linux::load(const CS_C_STR apiName)
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

void Linux::unload()
{
	if (m_API)
	{
		dlclose(m_API);
		m_API = nullptr;
		m_CreateShellFunc = nullptr;
	}
}

CS::Shell* Linux::CreateShell()
{
	if (m_CreateShellFunc)
		return m_CreateShellFunc();

	return nullptr;
}

Linux::Linux()
{
	m_SysCommands.insert({ "clear", { "clear", "w" } });
}

Linux& Linux::Get()
{
	static Linux instance{};
	return instance;
}

#endif