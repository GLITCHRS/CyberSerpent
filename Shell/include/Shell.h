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
		Shell();
		Shell(Shell&) = delete;

	public:
		/*
		*
		*  GENERAL COMMANDS
		*
		*/
		void help();
		void clear();
		virtual void back();
		virtual void exit();
		virtual void modules();

	public:
		static Shell& Get()
		{
			static Shell instance{};
			return instance;
		}

	public:
		System& m_Sys{ System::Get() };
		std::map<std::string, void(CS::Shell::*)()> m_Commands;

	public:
		static const char* s_ShellPrefix;
	};
}