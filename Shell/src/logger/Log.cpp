#include "logger/Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

void CS::Log::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	m_CoreLogger = spdlog::stdout_color_mt("CORE");
	m_ShellLogger = spdlog::stdout_color_mt("SHELL");
	m_CoreLogger->set_level(spdlog::level::trace);
	m_ShellLogger->set_level(spdlog::level::trace);
}

std::shared_ptr<spdlog::logger>& CS::Log::GetCoreLogger()
{
	return m_CoreLogger;
}

std::shared_ptr<spdlog::logger>& CS::Log::GetShellLogger()
{
	return m_ShellLogger;
}