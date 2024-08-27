#include "pch/pch.h"
#include "Shell.h"

#include <iostream>

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

class exception_exit : std::exception {};

 void CS::Shell::exit()
{
    throw exception_exit{};
}

 void CS::Shell::modules()
{
}