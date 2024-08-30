#pragma once

#include <string>

class Windows;
class Linux;

class System
{
public:
	virtual bool IsRoot() const = 0;
	virtual std::string ExecCommands(const std::string&) const = 0;

public:
	System(System&) = delete;

public:
	virtual ~System() = default;

public:
	static System& Get();

private:
	System() = default;
	friend class Windows;
	friend class Linux;
};