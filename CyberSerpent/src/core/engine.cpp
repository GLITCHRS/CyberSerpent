#include "core/Engine.h"

#include "Shell.h"
#include "pch/PCH.h"

#ifdef CS_DIST
#define ISROOT m_Shell->IsRoot()
#else
#define ISROOT true
#endif

void CS::CORE::Engine::Run()
{
	if (!ISROOT)
	{
		std::cout << "This tool requires being a root to use!\n";
		return;
	}

	std::string command;
	while (true)
	{
		std::cout << m_Shell->m_ShellPrefix;
		std::getline(std::cin, command);
		try
		{
			CS::Shell::MemberFuncPtr commandPtr{ m_Shell->GetCommand(command) };

			if (commandPtr)
				(m_Shell->*commandPtr)();
		}
		catch (exception_exit&)
		{
			break;
		}
	}
}

CS::CORE::Engine::Engine()
	: m_Shell(&CS::Shell::Get()) {}

CS::CORE::Engine& CS::CORE::Engine::Get()
{
	static Engine instance{};
	return instance;
}