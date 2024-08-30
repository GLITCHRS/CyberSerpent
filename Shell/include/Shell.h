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
		using MemberFuncPtr = void(Shell::*)();

	public:
		Shell(Shell&) = delete;

	public:
		/*
		*
		*  GENERAL COMMANDS
		*
		*/
		// unoverrided methods
		void Clear();

		// possibly overrided methods
		virtual void Help();
		virtual void Exit();
		virtual void Modules();
		virtual void Back();

		virtual bool IsRoot();

	public:
		MemberFuncPtr GetCommand(const std::string& command);

	private:
		inline bool IsValidCommand(const std::string&);

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
		std::map<std::string, MemberFuncPtr> m_Commands;

	public:
		const char* m_ShellPrefix;
	};
}