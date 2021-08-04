#include "Logger.h"

namespace Hi {

	std::shared_ptr<spdlog::logger> Logger::m_console;

	void Logger::Init()
	{
		m_console = spdlog::stdout_color_mt("HiRender");
		m_console->set_pattern("%^[%T] %n in (%@) : %v %$");
		m_console->set_level(spdlog::level::trace);
		m_console->trace("Logger created !");
	}
}