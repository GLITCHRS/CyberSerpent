#include "pch/pch.h"
#include "Shell.h"

#include "system/windows/Windows.h"

CS::Shell::Shell()
    : m_ShellPrefix("CyberSerpent>")
{
    m_Commands.emplace("help", &CS::Shell::Help);
    m_Commands.emplace("exit", &CS::Shell::Exit);
    m_Commands.emplace("clear", &CS::Shell::Clear);
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

void CS::Shell::Clear()
{
     m_Sys.Clear();
}

bool CS::Shell::IsRoot()
{
    return m_Sys.IsRoot();
}

void CS::Shell::Exit()
{
    throw exception_exit{};
}

void CS::Shell::Modules()
{
}

void CS::Shell::Back() {}