#pragma once

#include "OpenGlApplication.h"
#include "Logger.h"

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

std::shared_ptr<OpenGLApplication> application;

int main()
{
	uint32_t width = 800;
	uint32_t height = 600;
    application = std::make_shared<OpenGLApplication>(OpenGLApplication(width, height));
	Hi::Logger::Init();
	
	try
	{
		application.get()->Init();
		glfwSetFramebufferSizeCallback(application.get()->GetWindow(), [](GLFWwindow* window, int width, int height) {
			application.get()->FrameBufferSizeCallback(window, width, height);
			});

		glfwSetCursorPosCallback(application.get()->GetWindow(), [](GLFWwindow* window, double xpos, double ypos) {
			application.get()->mouse_callback(window, xpos, ypos);
			});
		glfwSetScrollCallback(application.get()->GetWindow(), [](GLFWwindow* window, double xoffset, double yoffset) {
			application.get()->scroll_callback(window, xoffset, yoffset);
			});

		application.get()->Run();
	}
	catch (const std::exception& e)
	{
		HI_ERROR(e.what());
		return EXIT_FAILURE;
	}
    
    return EXIT_SUCCESS;
}
