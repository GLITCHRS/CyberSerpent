#pragma once

#include <string>

#ifdef CS_WINDOWS
#include <Windows.h>
#define CS_C_STR wchar_t*
#define API_TYPE HMODULE
#else
#define CS_C_STR char*
#define API_TYPE void*
#endif

// forward decls
class Windows;
class Linux;
namespace CS
{
	class Shell;
}

// typedefs
typedef CS::Shell* (*CreateShellFuncPtr)();

class System
{
public:
	virtual bool IsRoot() const = 0;
	virtual std::string ExecCommands(const std::string&) const = 0;
	virtual bool load(const CS_C_STR) = 0;
	virtual void unload() = 0;
	virtual CS::Shell* CreateShell() = 0;

public:
	virtual ~System() = default;

public:
	System(System&) = delete;

public:
	static System& Get();

private:
	System() = default;
	friend class Windows;
	friend class Linux;

private:
	API_TYPE m_API;
	const char* m_APIName;
	CreateShellFuncPtr m_CreateShellFunc;
};