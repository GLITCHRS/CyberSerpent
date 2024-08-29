#include "core/engine.h"

#include "utils/root_check.h"
#include "Shell.h"

CS::Shell& CS::CORE::Engine::m_Shell{ CS::Shell::Get() };

void CS::CORE::Engine::Run()
{
	if (CS::UTILS::IsRoot())
		std::cout << "ROOT!\n";
	else
		std::cout << ":(\n";

	std::string command;
	while (true)
	{
		std::cout << CS::Shell::s_ShellPrefix;
		std::cin >> command;

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