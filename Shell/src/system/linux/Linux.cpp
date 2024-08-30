#ifndef CS_WINDOWS

#include "system/linux/Linux.h"

#include "pch/pch.h"
#include <unistd.h>

bool Linux::IsRoot() const
{
	return getuid() == 0;
}

void Linux::Clear() const
{
	FILE* pipe = popen("clear", "w");
	if (pipe)
		pclose(pipe);
}

Linux& Linux::Get()
{
	static Linux instance{};
	return instance;
}

#endif