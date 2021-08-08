#include "OpenGlApplication.h"

OpenGLApplication::OpenGLApplication(uint32_t& width, uint32_t& height)
{
	this->m_width = width;
	this->m_height = height;
	this->window = nullptr;
}

void OpenGLApplication::Run()
{

	this->Init();

	while (!glfwWindowShouldClose(this->window))
	{
        ProcessInput();

        glClearColor(1.0f, 0.7f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

       
        glUseProgram(this->shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);


		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
	glfwDestroyWindow(this->window);
	glfwTerminate();
}

void OpenGLApplication::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

std::string OpenGLApplication::readFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error(std::string{ "échec de l'ouverture du fichier " } + filename + "!");
    }
    
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return str;
}

unsigned int OpenGLApplication::CompileShader(GLenum shaderType, const std::string& filename)
{
    unsigned int shader = glCreateShader(shaderType);
    std::string str = readFile(filename);
    const char* shaderSource = str.c_str();
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    return shader;
}

void OpenGLApplication::RegisterShaderProgram(const std::string& vertFile, const std::string& fragFile)
{

    int success;
    char infoLog[512];

    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertFile);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        HI_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED : {0}", infoLog);
    }
   
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragFile);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        HI_ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED : {0}", infoLog);
    }


    this->shaderProgram = glCreateProgram();
    glAttachShader(this->shaderProgram, vertexShader);
    glAttachShader(this->shaderProgram, fragmentShader);
    glLinkProgram(this->shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        HI_ERROR("ERROR::SHADER::LINK::COMPILATION_FAILED : {0}", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

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
    
    RegisterShaderProgram("shaders/shader.vert", "shaders/shader.frag");

    float vertices[] = {
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f, 
    -0.5f,  0.5f, 0.0f  
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void OpenGLApplication::ProcessInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
