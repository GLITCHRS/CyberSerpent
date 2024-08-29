#pragma once

#include "system/System.h"

#include <iostream>

class Windows : public System
{
public:
	void clear() const override
	{
		FILE* pipe = _popen("cls", "w");
		if (pipe)
			_pclose(pipe);
	}
};