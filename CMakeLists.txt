cmake_minimum_required(VERSION 3.16)
project(gemelo LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(gemelo
    src/main.cpp
    src/core/Aplicacion.cpp
    src/render/Shader.cpp
    src/render/Malla.cpp
    src/camaras/Camara.cpp
    src/camaras/CamaraLibre.cpp
    src/objetos/Suelo.cpp
)
target_include_directories(gemelo PRIVATE src)
target_link_libraries(gemelo PRIVATE GLEW::GLEW glfw OpenGL::GL glm::glm)