add_rules("mode.debug", "mode.release")

add_requires("spdlog", "glfw", "vulkan-tools", "glad", "stb", "glm")

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

    set_rundir("./bin/vulkan/$(os)_$(arch)_$(mode)")
    set_targetdir("./bin/vulkan/$(os)_$(arch)_$(mode)")

    set_symbols("debug")
    after_build(function (target) 
        os.cp("$(projectdir)\\shaders\\*.spv", "$(projectdir)\\bin\\vulkan\\$(os)_$(arch)_$(mode)\\shaders\\")
    end)
target_end()

target("HiRenderOpenGL")
    set_version("0.0.1")
    set_kind("binary")
    
    add_files("src/HiRender/opengl/*.cpp")
    add_headerfiles("src/HiRender/opengl/*.h")

    add_packages("spdlog", "glfw", "glad", "stb", "glm") 
    add_syslinks("opengl32")
    
    
    set_rundir("./bin/opengl/$(os)_$(arch)_$(mode)")
    set_targetdir("./bin/opengl/$(os)_$(arch)_$(mode)")

    set_symbols("debug")
    after_build(function (target)         
        os.cp("$(projectdir)\\shaders\\*.vert", "$(projectdir)\\bin\\opengl\\$(os)_$(arch)_$(mode)\\shaders\\")
        os.cp("$(projectdir)\\shaders\\*.frag", "$(projectdir)\\bin\\opengl\\$(os)_$(arch)_$(mode)\\shaders\\")
        os.cp("$(projectdir)\\resources\\textures\\*", "$(projectdir)\\bin\\opengl\\$(os)_$(arch)_$(mode)\\resources\\textures\\")
    end)
target_end()