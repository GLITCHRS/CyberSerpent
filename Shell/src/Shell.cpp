#include "pch/pch.h"
#include "Shell.h"

#include <iostream>

CS::Shell::Shell()
    : m_ShellPrefix("CyberSerpent>")
{
    m_Commands.emplace("exit", &CS::Shell::exit);
    m_Commands.emplace("clear", &CS::Shell::clear);
}

void CS::Shell::help()
{
}

void CS::Shell::clear()
{
     m_Sys.clear();
}

 void CS::Shell::back()
{
}

 void CS::Shell::exit()
{
    throw exception_exit{};
}

 void CS::Shell::modules()
{
}