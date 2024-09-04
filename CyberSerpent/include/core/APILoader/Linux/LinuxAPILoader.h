#pragma once

#include "core/APILoader/APILoader.h"

typedef CS::Shell* (*CreateShellFuncPtr)();

class LinuxAPILoader : public APILoader
{
public:
	bool load(const wchar_t*) override;
	void unload() override;
	CS::Shell* CreateShell() override;

private:
	LinuxAPILoader() = default;

public:
	static LinuxAPILoader& Get();

private:
	void* m_API;
	const char* m_APIName;
	CreateShellFuncPtr m_CreateShellFunc;
};
