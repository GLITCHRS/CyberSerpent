#ifdef CS_WINDOWS

#include "system/windows/Windows.h"

#include "pch/pch.h"
#include <Windows.h>


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

void Windows::Clear() const
{
	FILE* pipe = _popen("cls", "w");
	if (pipe)
		_pclose(pipe);
}

Windows& Windows::Get()
{
	static Windows instance{};
	return instance;
}

#endif