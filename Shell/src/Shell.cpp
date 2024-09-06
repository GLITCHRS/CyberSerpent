#include "Shell.h"

#include "pch/pch.h"
#include "system/windows/Windows.h"

void CS::Shell::Clear()
{
    std::string commandResult{ m_Sys.ExecCommands("clear") };
}

void CS::Shell::Help()
{
    std::cout <<
R"###(
==================================================
help: displays this message
clear: clears the console
exit: exits the tool
modules: displays a list of available modules
==================================================

)###";
}

void CS::Shell::Exit()
{
    throw exception_exit{};
}

void CS::Shell::Modules() {}
void CS::Shell::Back() {}

bool CS::Shell::IsRoot()
{
    return m_Sys.IsRoot();
}

CS::Shell::MemberFuncPtr CS::Shell::GetCommand(const std::string& command)
{
    if (!IsValidCommand(command))
    {
        // CS::Log::warn("Command Don't Exist");
        return {};
    }

    return m_Commands.at(command);
}

inline bool CS::Shell::IsValidCommand(const std::string& command)
{
    return m_Commands.contains(command);
}

CS::Shell::Shell()
    : m_ShellPrefix("CyberSerpent>")
{
    m_Commands.emplace("help", &CS::Shell::Help);
    m_Commands.emplace("exit", &CS::Shell::Exit);
    m_Commands.emplace("clear", &CS::Shell::Clear);
}

CS::Shell& CS::Shell::Get()
{
    static Shell instance{};
    return instance;
}