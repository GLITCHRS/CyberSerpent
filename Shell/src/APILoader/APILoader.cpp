#include "APILoader/APILoader.h"
#include "APILoader/Windows/WinAPILoader.h"
#include "APILoader/Linux/LinuxAPILoader.h"

APILoader& APILoader::Get()
{
#ifdef CS_WINDOWS
	return WinAPILoader::Get();
#else
	return LinuxAPILoader::Get();
#endif
}