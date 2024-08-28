#include "pch/pch.h"
#include "Shell.h"

#include <iostream>

const char* CS::Shell::s_ShellPrefix{ "CyberSerpent>" };

CS::Shell::Shell()
{
    m_Commands.emplace("exit", &CS::Shell::exit);
    m_Commands.emplace("clear", &CS::Shell::clear);
}

void CS::Shell::help()
{
}

 void CS::Shell::clear()
{
#ifdef _WIN32
    FILE* pipe = _popen("cls", "w");
#else
    FILE* pipe = _popen("clear", "w");
#endif
    if (pipe)
        _pclose(pipe);
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