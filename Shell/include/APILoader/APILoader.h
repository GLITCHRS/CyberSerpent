#pragma once

#ifdef CS_WINDOWS
#define C_STR wchar_t*
#else
#define C_STR char*
#endif

namespace CS
{
	// forward decls
	class Shell;
}

class APILoader
{
public:
	virtual bool load(const C_STR) = 0;
	virtual void unload() = 0;
	virtual CS::Shell* CreateShell() = 0;

public:
	static APILoader& Get();
};