#pragma once

#ifdef CS_WINDOWS
#ifdef DLLExport
#define CyberSerpent_API __declspec(dllexport)
#else
#define CyberSerpent_API __declspec(dllimport)
#endif
#else
#ifdef DLLExport
#define CyberSerpent_API __attribute__((visibility("default")))
#else
#define CyberSerpent_API
#endif
#endif

#include "system/System.h"

#include <map>
#include <string>


class exception_exit : std::exception {};


namespace CS
{
	class CyberSerpent_API Shell
	{
	public:
		using MemberFuncPtr = void(Shell::*)();

	public:
		Shell(Shell&) = delete;

	public:
		/*
		*
		*  GENERAL COMMANDS (ACCESSABLE BY USER)
		*
		*/
		// unoverrided methods
		void Clear();

		// possibly overrided methods
		virtual void Help();
		virtual void Exit();
		virtual void Modules();
		virtual void Back();

	public:
		/*
		*
		*  GENERAL COMMANDS (UNACCESSABLE BY USER)
		*
		*/
		virtual bool IsRoot();

	public:
		MemberFuncPtr GetCommand(const std::string&);

	private:
		inline bool IsValidCommand(const std::string&);

	private:
		Shell();

	public:
		static Shell& Get();

	private:
		System& m_Sys{ System::Get() };
		std::map<std::string, MemberFuncPtr> m_Commands;

	public:
		const char* m_ShellPrefix;
	};
}

extern "C" CyberSerpent_API CS::Shell* createShell();
