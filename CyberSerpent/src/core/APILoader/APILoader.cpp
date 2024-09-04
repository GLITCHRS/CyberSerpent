#include "core/APILoader/APILoader.h"

#include "core/APILoader/Windows/WinAPILoader.h"

APILoader& APILoader::Get()
{
#ifdef CS_WINDOWS
	return WinAPILoader::Get();
#else
#endif
}

APILoader::~APILoader()
{
}
