#include "core/engine.h"
#include "core/APILoader/APILoader.h"

#include "Shell.h"

#include <iostream>

CS::CORE::Engine::Engine()
	: m_APILoader(APILoader::Get()), m_Shell(nullptr)
{
#ifdef CS_WINDOWS
	const wchar_t* apiName{ L"Shell.dll" };
#else
	const wchar_t* apiName{ "./Shell.so" };
#endif

	if (!m_APILoader.load(apiName))
	{
		return;
	}

	m_Shell = m_APILoader.CreateShell();
}

CS::CORE::Engine& CS::CORE::Engine::Get()
{
	static Engine instance{};
	return instance;
}

void CS::CORE::Engine::Run()
{
#ifdef CS_DIST
	if (!m_Shell->IsRoot())
	{
		std::cout << "This tool requires being a root to use!\n";
		std::cin.get();
		return;
	}
#endif

	if (!m_Shell)
		return;

	std::string command;
	while (true)
	{
		std::cout << m_Shell->m_ShellPrefix;
		std::getline(std::cin, command);
		try
		{
			auto commandPtr{ m_Shell->GetCommand(command) };

			if (commandPtr)
				(m_Shell->*commandPtr)();
		}
		catch (exception_exit&)
		{
			break;
		}
	}
}