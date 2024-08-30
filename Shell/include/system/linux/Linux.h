#pragma once

#include "system/System.h"

class Linux : public System
{
public:
	bool IsRoot() const override;
	void Clear() const override;

public:
	static Linux& Get();

private:
	Linux() = default;
};