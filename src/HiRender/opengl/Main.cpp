#pragma once

#include "OpenGlApplication.h"
#include "Logger.h"


int main()
{
	uint32_t width = 800;
	uint32_t height = 600;
    OpenGLApplication application(width, height);
	Hi::Logger::Init();
	
	try
	{
		application.Run();
	}
	catch (const std::exception& e)
	{
		HI_ERROR(e.what());
		return EXIT_FAILURE;
	}
    
    return EXIT_SUCCESS;
}