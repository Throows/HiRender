#pragma once

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <vulkan/vulkan.hpp>

#define HI_TRACE(...) console->trace(__VA_ARGS__)
#define HI_DEBUG(...) console->debug(__VA_ARGS__)
#define HI_INFO(...) console->info(__VA_ARGS__)
#define HI_WARN(...) console->warn(__VA_ARGS__)
#define HI_ERROR(...) console->error(__VA_ARGS__)

int main(void)
{

    auto console = spdlog::stdout_color_mt("HiRender");
    console->set_pattern("%^[%T] %n in (%@) : %v %$");
    console->set_level(spdlog::level::trace);

    GLFWwindow* window;
    VkInstance instance;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    HI_TRACE("GLFW Init successfully !");

    window = glfwCreateWindow(640, 480, "HIRender", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    } 

    HI_TRACE("Window created successfully !");

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "HiRender - Vulkan";
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;


    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    createInfo.enabledLayerCount = 0;

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        HI_ERROR("Failed to create Vulkan Instance !");
    }
    HI_TRACE("Vulkan initialized successfully !");


    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    vkDestroyInstance(instance, nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}