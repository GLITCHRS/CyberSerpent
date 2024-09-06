#pragma once

#include "system/System.h"
#include <map>

// forward decls
struct Command;

class Linux : public System
{
public:
	std::string ExecCommands(const std::string&) const override;

public:
	bool IsRoot() const override;

public:
	bool load(const CS_C_STR);
	void unload();
	CS::Shell* CreateShell();

private:
	Linux();

public:
	static Linux& Get();

public:
	std::map<std::string, Command> m_SysCommands;
};