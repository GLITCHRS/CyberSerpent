#include "Log/Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger>& CS::Log::GetLogger()
{
	return m_Logger;
}

CS::Log::Log()
{
	spdlog::set_pattern("%^[%T]: %v%$");
	m_Logger = spdlog::stdout_color_mt("CyberSerpent");
	m_Logger->set_level(spdlog::level::trace);
}

CS::Log& CS::Log::Get()
{
	static Log instance{};
	return instance;
}
