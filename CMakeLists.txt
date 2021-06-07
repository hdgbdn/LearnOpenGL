cmake_minimum_required(VERSION 3.3)
project(LearnOpenGL)

# find packages
if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()
find_package(OpenGL REQUIRED)

# include
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

# flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add subdirectory glm GLAD GLFW 
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/3rd/glfw)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/3rd/glad)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/3rd/assimp)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/3rd/glm)

add_executable("hdr" src/hdr.cpp src/Camera.cpp src/Shader.cpp)
target_link_libraries("hdr" glad glfw OpenGL::GL assimp glm::glm)

add_executable("bloom" src/bloom.cpp src/Camera.cpp src/Shader.cpp)
target_link_libraries("bloom" glad glfw OpenGL::GL assimp)

add_executable("deffered" src/deffered.cpp src/Camera.cpp src/Shader.cpp)
target_link_libraries("deffered" glad glfw OpenGL::GL assimp)

add_executable("SSAO" src/SSAO.cpp src/Camera.cpp src/Shader.cpp)
target_link_libraries("SSAO" glad glfw OpenGL::GL assimp)

add_executable("pbr" src/pbr.cpp src/Camera.cpp src/Shader.cpp)
target_link_libraries("pbr" glad glfw OpenGL::GL assimp)

add_executable("IBL_Diffuse" src/IBL_Diffuse.cpp src/Camera.cpp src/Shader.cpp)
target_link_libraries("IBL_Diffuse" glad glfw OpenGL::GL assimp)

add_executable("IBL_Specular" src/IBL_Specular.cpp src/Camera.cpp src/Shader.cpp)
target_link_libraries("IBL_Specular" glad glfw OpenGL::GL assimp)
