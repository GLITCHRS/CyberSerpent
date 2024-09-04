#include "core/Engine.h"

#include "Shell.h"
#include "pch/PCH.h"
#include "core/APILoader/APILoader.h"

#ifdef CS_WINDOWS
#define API_NAME L"Shell.dll"
#else
#define API_NAME L"./Shell.so"
#endif

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

	if (!m_Shell)
	{
		std::cerr << "m_Shell is nullptr, failed to create shell\n";
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
	: m_APILoader(APILoader::Get()), m_Shell(nullptr)
{
	if (!m_APILoader.load(API_NAME))
		return;

	m_Shell = m_APILoader.CreateShell();
}

CS::CORE::Engine::~Engine()
{
	m_APILoader.unload();
}

CS::CORE::Engine& CS::CORE::Engine::Get()
{
	static Engine instance{};
	return instance;
}