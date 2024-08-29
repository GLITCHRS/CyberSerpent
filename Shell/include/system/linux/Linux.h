#pragma once

#include "system/System.h"

#include <iostream>

class Linux : public System
{
public:
	void clear() const override
	{
		FILE* pipe = popen("clear", "w");
		if (pipe)
			pclose(pipe);
	}
};