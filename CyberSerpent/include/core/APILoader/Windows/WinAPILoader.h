#ifdef CS_WINDOWS

#pragma once

#include "core/APILoader/APILoader.h"
#include <Windows.h>

typedef CS::Shell* (*CreateShellFuncPtr)();

class WinAPILoader : public APILoader
{
public:
	bool load(const C_STR) override;
	void unload() override;
	CS::Shell* CreateShell() override;

private:
	WinAPILoader() = default;

public:
	static WinAPILoader& Get();

private:
	const char* m_APIName;
	HMODULE m_API;
	CreateShellFuncPtr m_CreateShellFunc;
};

#endif