#pragma once

#include "spdlog/spdlog.h"
#include <memory>

// Log Macros
#if defined(CS_DEBUG) || defined(CS_RELEASE)
#define  CS_TRACE(...) CS::Log::GetLogger()->trace(__VA_ARGS__)
#define  CS_INFO(...)  CS::Log::GetLogger()->info(__VA_ARGS__)
#define  CS_WARN(...)  CS::Log::GetLogger()->warn(__VA_ARGS__)
#define  CS_ERROR(...) CS::Log::GetLogger()->error(__VA_ARGS__)
#define  CS_FATAL(...) CS::Log::GetLogger()->fatal(__VA_ARGS__)
#else
#define  CS_TRACE(...)
#define  CS_INFO(...) 
#define  CS_WARN(...) 
#define  CS_ERROR(...)
#define  CS_FATAL(...)
#endif

namespace CS
{
	class Log
	{
	public:
		Log() = delete;

	public:
		static void Init();
		static std::shared_ptr<spdlog::logger>& GetLogger();

	private:
		static inline std::shared_ptr<spdlog::logger> m_Logger{};
	};
}