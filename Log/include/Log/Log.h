#pragma once

#include "spdlog/spdlog.h"
#include <memory>

// Log Macros
#if defined(CS_DEBUG) || defined(CS_RELEASE)
#define  CS_TRACE(...) CS::Log::Get().GetLogger()->trace(__VA_ARGS__)
#define  CS_INFO(...)  CS::Log::Get().GetLogger()->info(__VA_ARGS__)
#define  CS_WARN(...)  CS::Log::Get().GetLogger()->warn(__VA_ARGS__)
#define  CS_ERROR(...) CS::Log::Get().GetLogger()->error(__VA_ARGS__)
#define  CS_FATAL(...) CS::Log::Get().GetLogger()->fatal(__VA_ARGS__)
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
		std::shared_ptr<spdlog::logger>& GetLogger();

	private:
		Log();

	public:
		Log(Log&) = delete;

	public:
		static Log& Get();

	private:
		std::shared_ptr<spdlog::logger> m_Logger;
	};
}