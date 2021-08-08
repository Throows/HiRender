#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iterator>
#include <fstream>

#include "Logger.h"

class OpenGLApplication
{
public:
	OpenGLApplication(uint32_t &width, uint32_t &height);
	
	void Run();

	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	std::string readFile(const std::string& filename);
	unsigned int CompileShader(GLenum shaderType, const std::string& filename);
	void RegisterShaderProgram(const std::string& vertFile, const std::string& fragFile);

private:
	GLFWwindow* window;
	uint32_t m_width;
	uint32_t m_height;

	unsigned int shaderProgram;

	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	void Init();
	void ProcessInput();
};