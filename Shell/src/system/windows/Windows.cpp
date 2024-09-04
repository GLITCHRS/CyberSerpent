#ifdef CS_WINDOWS

#include "system/windows/Windows.h"

#include "pch/pch.h"
#include "system/Command.h"
#include <Windows.h>

static std::string FileToString(FILE* file)
{
	std::string result;
	char buffer[128];

	while (fgets(buffer, sizeof(buffer), file) != nullptr)
		result += buffer;

	return result;
}

std::string Windows::ExecCommands(const std::string& command) const
{
	std::string commandResult{ "" };
	Command sysCommand{ m_SysCommands.at(command) };
	FILE* pipe = _popen(sysCommand.command.c_str(), sysCommand.mode.c_str());

	if (sysCommand.mode == "w")
	{
		commandResult = FileToString(pipe);
	}

	if (pipe)
		_pclose(pipe);

	return commandResult;
}

bool Windows::IsRoot() const
{
	BOOL isMember;
	PSID administratorsGroup = nullptr;
	SID_IDENTIFIER_AUTHORITY SIDAuthNT = SECURITY_NT_AUTHORITY;

	if (AllocateAndInitializeSid(&SIDAuthNT, 2, SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &administratorsGroup))
	{
		if (CheckTokenMembership(nullptr, administratorsGroup, &isMember))
		{
			FreeSid(administratorsGroup);
			return isMember != 0;
		}
		FreeSid(administratorsGroup);
	}
	return false;
}

Windows::Windows()
{
	m_SysCommands.insert({ "clear", { "cls", "w" } });
}

Windows& Windows::Get()
{
	static Windows instance{};
	return instance;
}

#endif