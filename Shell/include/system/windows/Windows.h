#pragma once

#include "system/System.h"


class Windows : public System
{
public:
	bool IsRoot() const override;
	void Clear() const override;

public:
	static Windows& Get();

private:
	Windows() = default;
};