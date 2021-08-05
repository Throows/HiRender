add_rules("mode.debug", "mode.release")

add_requires("spdlog", "glfw", "vulkan-tools", "glm")

set_runtimes("MD")
set_languages("cxx17")

target("HiRender")
    set_version("0.0.1")

    set_kind("binary")

    add_files("src/*.cpp")
    add_headerfiles("src/*.h")
    add_includedirs("include/")
    add_includedirs("shaders/")
    add_packages("spdlog", "glfw", "vulkan-tools", "glm") 
    add_syslinks("vulkan-1")
    set_symbols("debug")
    after_build(function (target) 
        -- TODO impl to move /shaders
        print("moving files ! to : $(projectdir)\\shaders\\*.spv")
        os.cp("$(projectdir)\\shaders\\*.spv", "$(projectdir)\\$(buildir)\\$(plat)\\$(arch)\\$(mode)\\shaders\\")

    end)
    