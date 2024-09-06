#pragma once

#include "spdlog/spdlog.h"
#include <memory>

// Log Macros
#if defined(CS_DEBUG) || defined(CS_RELEASE)
#define  CS_CORE_TRACE(...) CS::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define  CS_CORE_INFO(...)  CS::Log::GetCoreLogger()->info(__VA_ARGS__)
#define  CS_CORE_WARN(...)  CS::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define  CS_CORE_ERROR(...) CS::Log::GetCoreLogger()->error(__VA_ARGS__)
#define  CS_CORE_CRITICAL(...) CS::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define  CS_SHELL_TRACE(...) CS::Log::GetShellLogger()->trace(__VA_ARGS__)
#define  CS_SHELL_INFO(...)  CS::Log::GetShellLogger()->info(__VA_ARGS__)
#define  CS_SHELL_WARN(...)  CS::Log::GetShellLogger()->warn(__VA_ARGS__)
#define  CS_SHELL_ERROR(...) CS::Log::GetShellLogger()->error(__VA_ARGS__)
#define  CS_SHELL_CRITICAL(...) CS::Log::GetShellLogger()->critical(__VA_ARGS__)
#else
#define  CS_CORE_TRACE(...)
#define  CS_CORE_INFO(...) 
#define  CS_CORE_WARN(...) 
#define  CS_CORE_ERROR(...)
#define  CS_CORE_CRITICAL(...) CS::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define  CS_SHELL_TRACE(...)
#define  CS_SHELL_INFO(...) 
#define  CS_SHELL_WARN(...) 
#define  CS_SHELL_ERROR(...)
#define  CS_SHELL_CRITICAL(...) CS::Log::GetShellLogger()->critical(__VA_ARGS__)
#endif

namespace CS
{
	class Log
	{
	public:
		Log() = delete;

	public:
		static void Init();
		static std::shared_ptr<spdlog::logger>& GetCoreLogger();
		static std::shared_ptr<spdlog::logger>& GetShellLogger();

	private:
		static inline std::shared_ptr<spdlog::logger> m_CoreLogger{};
		static inline std::shared_ptr<spdlog::logger> m_ShellLogger{};
	};
}