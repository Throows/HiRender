#pragma once

#define GLFW_INCLUDE_GLU
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

    HI_INFO("Init ! {0}", 0);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    } 

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}