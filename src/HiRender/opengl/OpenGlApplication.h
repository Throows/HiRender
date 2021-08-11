#pragma once

#include <stb_image.h>
#include "Shader.h"
#include "Camera.h"


class OpenGLApplication
{
public:
	OpenGLApplication(uint32_t &width, uint32_t &height);
	
	void Init();
	void RegisterCallBacks(OpenGLApplication& application);
	void Run();

	void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	GLFWwindow* GetWindow() { return this->window; }

private:
	GLFWwindow* window;

	Hi::Shader shader;
	unsigned int texture = 0;

	uint32_t m_width;
	uint32_t m_height;

	unsigned int VBO = 0;
	unsigned int VAO = 0;
	//unsigned int EBO;

	Hi::Camera camera;
	float lastX;
	float lastY;
	bool firstMouse;

	float deltaTime = 0.0f;	
	float lastFrame = 0.0f;

	void ProcessInput();
};