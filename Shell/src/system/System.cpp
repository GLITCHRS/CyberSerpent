#include "system/System.h"

#ifdef _WIN32
#include "system/windows/Windows.h"
#else
#include "system/linux/Linux.h"
#endif

System& System::Get()
{
#ifdef _WIN32
	static Windows sys{};
#else
	static Linux sys{};
#endif
	return sys;
}