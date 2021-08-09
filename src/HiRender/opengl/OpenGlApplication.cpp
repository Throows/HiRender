#include "OpenGlApplication.h"

OpenGLApplication::OpenGLApplication(uint32_t& width, uint32_t& height)
{
	this->m_width = width;
	this->m_height = height;
	this->window = nullptr;
    this->shader = Hi::Shader();
}

void OpenGLApplication::Run()
{

	this->Init();

	while (!glfwWindowShouldClose(this->window))
	{
        ProcessInput();

        glClearColor(1.0f, 0.7f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float redValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shader.getShaderProgram(), "ourColor");
        glUniform4f(vertexColorLocation, redValue, 0.0f, 0.0f, 1.0f);

       
        shader.UseShader();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);


		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader.getShaderProgram());
    glfwDestroyWindow(this->window);
	glfwTerminate();
}

void OpenGLApplication::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void OpenGLApplication::Init()
{

	if (!glfwInit())
	{
		HI_ERROR("GLFW failed initialization !");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(this->m_width, this->m_height, "OpenGL Application", nullptr, nullptr);

	glfwMakeContextCurrent(this->window);

	glfwSetFramebufferSizeCallback(this->window, FrameBufferSizeCallback);
    

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		HI_ERROR("Failed to initialize GLAD");
	}

    glViewport(0, 0, this->m_width, this->m_height);
    
    this->shader.Init("shaders/shader.vert", "shaders/shader.frag");
    
    float vertices[] = {
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, 0.0f, 0.0f, 0.5f, 0.0f
    };

    unsigned int indices[] = { 
        0, 1, 3,   
        1, 2, 3    
    };


    glGenBuffers(1, &this->EBO);
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void OpenGLApplication::ProcessInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
