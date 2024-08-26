#pragma once

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

namespace CS
{
	class Engine
	{
	public:
		Engine() = default;
		Engine(Engine&) = delete;

	public:
		void Run() const
		{
			if (IsRoot())
				std::cout << "ROOT!\n";
			else
				std::cout << ":(\n";
		}
#ifdef _WIN32
		bool IsRoot() const
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
#else
		bool IsRoot() const
		{
			return getuid() == 0;
		}
#endif

	public:
		static Engine& Get()
		{
			static Engine s_Instance{};
			return s_Instance;
		}
	};
}