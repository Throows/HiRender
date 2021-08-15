#define BOUNCE(c,m) bounce<c, decltype(&c::m), &c::m>
#define STB_IMAGE_IMPLEMENTATION
#include "OpenGlApplication.h"

OpenGLApplication::OpenGLApplication(uint32_t& width, uint32_t& height)
{
    this->shader = Hi::Shader();
    this->window = nullptr;

    camera = Hi::Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    m_width = width;
    m_height = height;
    lastX = m_width / 2.0f;
    lastY = m_height / 2.0f;
    firstMouse = true;
}

void OpenGLApplication::Run()
{
    glm::vec3 cubePos = glm::vec3(0.0f, 0.0f, 0.0f);

	while (!glfwWindowShouldClose(this->window))
	{

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ProcessInput();

        glClearColor(1.0f, 0.7f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->texture);
        
        shader.UseShader();
        glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (float)m_width / (float)m_height, 0.1f, 100.0f);
        shader.setMat4("projection", projection);

      
        glm::mat4 view = camera.GetViewMatrix();
        shader.setMat4("view", view);

        projection = glm::perspective(glm::radians(45.0f), (float)m_width / (float)m_height, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        
        glBindVertexArray(VAO);
     
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePos);
        float angle = /*2*/0.0f;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(3.5f, 1.0f, 2.0f));
        shader.setMat4("model", model);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);


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

void OpenGLApplication::Init()
{

    if (!glfwInit())
    {
        HI_ERROR("GLFW failed initialization !");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(m_width, m_height, "OpenGL Application", nullptr, nullptr);

    glfwMakeContextCurrent(this->window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		HI_ERROR("Failed to initialize GLAD");
	}

    glEnable(GL_DEPTH_TEST);

    glfwSetWindowUserPointer(this->window, this);
    RegisterCallbacks();

    glViewport(0, 0, m_width, m_height);
    
    this->shader.Init("shaders/shader.vert", "shaders/shader.frag");
    
    /*float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };*/

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,

         0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,  0.3f, 0.3f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.3f,
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.3f, 1.0f,

        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f
    };

    unsigned int indices[] = {
         0, 1, 2,
         2, 3, 0,

         4, 5, 6, 
         6, 7, 4,

         8,  9, 10,
        10, 11,  8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20

    };


    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); 
    unsigned char* data = stbi_load("resources/textures/grass.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        HI_ERROR("Failed to load texture");
    }
    stbi_image_free(data);

    shader.UseShader();

    glUniform1i(glGetUniformLocation(shader.getShaderProgram(), "myTexture"), 0);

    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &this->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    
    glBindVertexArray(this->VAO);
}

void OpenGLApplication::RegisterCallbacks()
{
    glfwSetFramebufferSizeCallback(this->window, [](GLFWwindow* window, int width, int height) {
        static_cast<OpenGLApplication*>(glfwGetWindowUserPointer(window))->FrameBufferSizeCallback(window, width, height);
        });
    glfwSetCursorPosCallback(this->window, [](GLFWwindow * window, double xPos, double yPos) {
        static_cast<OpenGLApplication*>(glfwGetWindowUserPointer(window))->mouse_callback(window, xPos, yPos);
        });

    glfwSetScrollCallback(this->window, [](GLFWwindow* window, double xOffset, double yOffset) {
        static_cast<OpenGLApplication*>(glfwGetWindowUserPointer(window))->scroll_callback(window, xOffset, yOffset);
        });
}

void OpenGLApplication::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    m_width = width;
    m_height = height;
}

void OpenGLApplication::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset, false);
}

void OpenGLApplication::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void OpenGLApplication::ProcessInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}
