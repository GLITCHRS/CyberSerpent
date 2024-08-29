#pragma once

class Windows;
class Linux;

class System
{
public:
	System(System&) = delete;

public:
	virtual ~System() = default;

public:
	virtual bool IsRoot() const = 0;
	virtual void Clear() const = 0;

public:
	static System& Get();

private:
	System() = default;
	friend class Windows;
	friend class Linux;
};