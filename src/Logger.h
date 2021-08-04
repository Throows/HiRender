#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Hi
{
	class Logger
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetLogger() { return m_console; };

	private:
		static std::shared_ptr<spdlog::logger> m_console;

	};

#define HI_TRACE(...)	Hi::Logger::GetLogger()->trace(__VA_ARGS__)
#define HI_DEBUG(...)	Hi::Logger::GetLogger()->debug(__VA_ARGS__)
#define HI_INFO(...)	Hi::Logger::GetLogger()->info(__VA_ARGS__)
#define HI_WARN(...)	Hi::Logger::GetLogger()->warn(__VA_ARGS__)
#define HI_ERROR(...)	Hi::Logger::GetLogger()->error(__VA_ARGS__)
}

