#include "Log/Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

void CS::Log::Init()
{
	spdlog::set_pattern("%^[%T]: %v%$");
	m_Logger = spdlog::stdout_color_mt("CyberSerpent");
	m_Logger->set_level(spdlog::level::trace);
}

std::shared_ptr<spdlog::logger>& CS::Log::GetLogger()
{
	return m_Logger;
}