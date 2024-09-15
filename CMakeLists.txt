cmake_minimum_required(VERSION 3.28)
project(triangleOpenGL2)

set(CMAKE_CXX_STANDARD 17)

add_executable(triangleOpenGL2 main.cpp
    shader.cpp
    shader.h
    stb_image.h
    stb_image.cpp
        stb_image.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/glad/include)
add_library(glad ${PROJECT_SOURCE_DIR}/glad/src/glad.c)
target_link_libraries(triangleOpenGL2 PRIVATE glad glfw OpenGL::GL)
include_directories(${PROJECT_SOURCE_DIR}/glm)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
