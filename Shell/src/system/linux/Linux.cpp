#ifndef CS_WINDOWS

#include "system/linux/Linux.h"

#include "pch/pch.h"
#include <unistd.h>

std::string Linux::ExecCommands(const std::string&) const
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

void Linux::Clear() const
{
	FILE* pipe = popen("clear", "w");
	if (pipe)
		pclose(pipe);
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