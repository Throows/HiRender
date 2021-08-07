add_rules("mode.debug", "mode.release")

add_requires("spdlog", "glfw", "vulkan-tools", "glad", "glm")

set_runtimes("MD")
set_languages("cxx17")

set_project("HiRender")

target("HiRenderVulkan")
    set_version("0.0.1")
    set_kind("binary")

    add_files("src/HiRender/vulkan/*.cpp")
    add_headerfiles("src/HiRender/vulkan/*.h")

    add_packages("spdlog", "glfw", "vulkan-tools", "glm") 
    add_syslinks("vulkan-1")

    set_symbols("debug")
    after_build(function (target) 
        -- TODO impl to move /shaders
        print("moving files ! to : $(projectdir)\\shaders\\*.spv")
        os.cp("$(projectdir)\\shaders\\*.spv", "$(projectdir)\\$(buildir)\\$(plat)\\$(arch)\\$(mode)\\shaders\\")

    end)
target_end()

target("HiRenderOpenGL")
    set_version("0.0.1")
    set_kind("binary")
    
    add_files("src/HiRender/opengl/*.cpp")
    add_headerfiles("src/HiRender/opengl/*.h")

    add_packages("spdlog", "glfw", "glad", "glm") 
    add_syslinks("opengl32")
    
    set_symbols("debug")
target_end()