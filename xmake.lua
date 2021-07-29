add_rules("mode.debug", "mode.release")

add_requires("spdlog", "glfw", "glew", "glm")

set_runtimes("MD")

target("HiRender")
    set_version("0.0.1")

    set_kind("binary")

    add_files("src/*.cpp")
    add_headerfiles("src/*.h")
    add_includedirs("include/")

    add_packages("spdlog", "glfw", "glew", "glm") 
    add_syslinks("opengl32")
    set_symbols("debug")