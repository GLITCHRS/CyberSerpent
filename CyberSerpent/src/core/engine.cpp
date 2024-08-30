#include "core/engine.h"

#include "Shell.h"

#include <iostream>

CS::Shell& CS::CORE::Engine::m_Shell{ CS::Shell::Get() };

void CS::CORE::Engine::Run()
{
#ifdef CS_DIST
	if (!m_Shell.IsRoot())
	{
		std::cout << "This tool requires being a root to use!\n";
		std::cin.get();
		return;
	}
#endif

	std::string command;
	while (true)
	{
		std::cout << m_Shell.m_ShellPrefix;
		std::getline(std::cin, command);
		try
		{
			auto commandPtr{ m_Shell.GetCommand(command) };

			if (commandPtr)
				(m_Shell.*commandPtr)();
		}
		catch (exception_exit&)
		{
			break;
		}
	}
}