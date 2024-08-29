#include "system/System.h"

#ifdef CS_WINDOWS
#include "system/windows/Windows.h"
#else
#include "system/linux/Linux.h"
#endif

System& System::Get()
{
#ifdef CS_WINDOWS
	return Windows::Get();
#else
	return Linux::Get();
#endif
}