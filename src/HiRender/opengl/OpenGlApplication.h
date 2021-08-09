#pragma once

#include "Shader.h"

class OpenGLApplication
{
public:
	OpenGLApplication(uint32_t &width, uint32_t &height);
	
	void Run();

	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

private:
	GLFWwindow* window;
	uint32_t m_width;
	uint32_t m_height;

	Hi::Shader shader;

	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	void Init();
	void ProcessInput();
};