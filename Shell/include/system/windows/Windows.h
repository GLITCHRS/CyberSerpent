#pragma once

#include "pch/pch.h"
#include "system/System.h"

#include <Windows.h>

class Windows : public System
{
public:
	bool IsRoot() const override
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

	void Clear() const override
	{
		FILE* pipe = _popen("cls", "w");
		if (pipe)
			_pclose(pipe);
	}

public:
	static Windows& Get()
	{
		static Windows instance{};
		return instance;
	}

private:
	Windows() = default;
};