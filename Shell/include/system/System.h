#pragma once

class Windows;
class Linux;

class System
{
public:
	System() = default;
	System(System&) = delete;

public:
	virtual ~System() = default;

public:
	virtual void clear() const = 0;

public:
	static System& Get();
};