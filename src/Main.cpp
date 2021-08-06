#pragma once

#include "VulkanApplication.h"
#include "Logger.h"


int main()
{
    VulkanApplication application;
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