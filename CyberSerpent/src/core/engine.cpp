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

		if (m_Shell.m_Commands.contains(command))
		{
			try
			{
				(m_Shell.*m_Shell.m_Commands[command])();
			}
			catch (exception_exit&)
			{
				break;
			}
		}
		else
		{
			std::cout << "Command (" << command << ") don't exist\n";
		}
	}
}