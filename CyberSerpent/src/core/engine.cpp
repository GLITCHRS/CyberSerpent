#include "core/Engine.h"

#include "Shell.h"
#include "pch/PCH.h"

#ifdef CS_DIST
#define ISROOT m_Shell->IsRoot()
#else
#define ISROOT true
#endif

std::vector<std::string> GetFlags(const std::string& str)
{
	std::vector<std::string> tokens;
	std::string token;

	for (char c : str)
	{
		if (c != ' ')
		{
			token += c;
			continue;
		}

		if (!token.empty())
		{
			tokens.push_back(token);
			token.clear();
		}
	}

	if (!token.empty())
		tokens.push_back(token);

	return tokens;
}

std::pair<std::string, std::vector<std::string>> SeparateCommandAndFlags(std::string text)
{
	std::string command{};
	std::vector<std::string> flags{ GetFlags(text) };
	if (flags.empty())
		return { text , std::vector<std::string>{} };

	command = flags[0];
	flags.erase(flags.begin());

	CS_CORE_WARN("Command: {}", command);
	for(auto flag : flags)
		CS_CORE_WARN("Flag: {}", flag);

	return { command, flags };
}

void CS::CORE::Engine::Run()
{
	if (!ISROOT)
	{
		CS_CORE_CRITICAL("This tool requires being a root to use!\n");
		return;
	}

	std::string input;

	while (true)
	{
		std::cout << m_Shell->m_ShellPrefix;

		std::getline(std::cin, input);
		std::pair<std::string, std::vector<std::string>> Command{ SeparateCommandAndFlags(input) };

		try
		{
			CS::Shell::MemberFuncPtr commandPtr{ m_Shell->GetCommand(Command.first) };

			if (commandPtr)
			{
				(m_Shell->*commandPtr)();
				continue;
			}

			CS::Shell::ModuleFuncPtr moduleCommandPtr{ m_Shell->GetModuleCommand(Command.first) };

			if (!moduleCommandPtr)
				continue;

			(m_Shell->*moduleCommandPtr)(Command.second);
		}
		catch (exception_exit&)
		{
			break;
		}
	}
}

CS::CORE::Engine::Engine()
	: m_Shell(&CS::Shell::Get())
{
	CS::Log::Init();
}

CS::CORE::Engine& CS::CORE::Engine::Get()
{
	static Engine instance{};
	return instance;
}