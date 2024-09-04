#include "core/APILoader/APILoader.h"
#include "core/APILoader/Windows/WinAPILoader.h"
#include "core/APILoader/Linux/LinuxAPILoader.h"

APILoader& APILoader::Get()
{
#ifdef CS_WINDOWS
	return WinAPILoader::Get();
#else
	return LinuxAPILoader::Get();
#endif
}