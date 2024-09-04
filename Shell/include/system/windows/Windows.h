#pragma once

#include "system/System.h"
#include <map>

// forward decls
struct Command;

class Windows : public System
{
public:
	std::string ExecCommands(const std::string&) const override;

public:
	bool IsRoot() const override;

private:
	Windows();

public:
	static Windows& Get();

public:
	std::map<std::string, Command> m_SysCommands;
};