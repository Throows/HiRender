#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#define HI_TRACE(...) console->trace(__VA_ARGS__)
#define HI_INFO(...) console->info(__VA_ARGS__)
#define HI_WARN(...) console->warn(__VA_ARGS__)
#define HI_ERROR(...) console->error(__VA_ARGS__)

int main(void)
{

    auto console = spdlog::stdout_color_mt("HiRender");
    console->set_pattern("%^[%T] %n in (%@) : %v %$");
    console->set_level(spdlog::level::trace);

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    HI_INFO("GLFW and GLEW Init successfully !");

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "HIRender", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    } 

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        HI_ERROR("ERROR ! FAILED TO INIT GLEW");
    }

    HI_INFO("OpenGL Context created ! Using version : {0}", glGetString(GL_VERSION));

    float pos[6] = {
        -0.5f, -0.5f,
         0.0f, 0.5f,
         0.5f, -0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), pos, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}