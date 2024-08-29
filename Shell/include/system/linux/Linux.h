#pragma once

#include "pch/pch.h"
#include "system/System.h"

#include <unistd.h>

class Linux : public System
{
public:
	bool IsRoot()
	{
		return getuid() == 0;
	}

	void Clear() const override
	{
		FILE* pipe = popen("clear", "w");
		if (pipe)
			pclose(pipe);
	}

public:
	static Linux& Get()
	{
		static Linux instance{};
		return instance;
	}

private:
	Linux() = default;
};