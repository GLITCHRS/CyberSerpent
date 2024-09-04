#pragma once

namespace CS
{
	// forward decls
	class Shell;
}

class APILoader
{
public:
	virtual bool load(const wchar_t*) = 0;
	virtual void unload() = 0;
	virtual CS::Shell* CreateShell() = 0;

public:
	static APILoader& Get();
};