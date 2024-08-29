#pragma once

/*
#ifdef _WIN32
#ifdef DLLExport
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif
#else
#define DLL __attribute__((visibility("default")))
#endif
*/

#include "system/System.h"

#include <map>
#include <string>


class exception_exit : std::exception {};


namespace CS
{
	class Shell
	{
	public:
		Shell(Shell&) = delete;

	public:
		/*
		*
		*  GENERAL COMMANDS
		*
		*/
		void Help();
		void Clear();
		virtual bool IsRoot();
		virtual void Back();
		virtual void Exit();
		virtual void Modules();

	public:
		static Shell& Get()
		{
			static Shell instance{};
			return instance;
		}

	private:
		Shell();

	public:
		System& m_Sys{ System::Get() };
		std::map<std::string, void(CS::Shell::*)()> m_Commands;

	public:
		const char* m_ShellPrefix;
	};
}