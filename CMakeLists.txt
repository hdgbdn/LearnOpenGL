cmake_minimum_required(VERSION 3.3)
project(LearnOpenGL)


# find packages
if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()
find_package(OpenGL REQUIRED)

# include
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/glfw/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/glm)
include_directories(${CMAKE_CURRENT_LIST_DIR}/assimp/include)


# execute
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(SOURCE_FILES main.cpp ${SRC_DIR}/Shader.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
message(STATUS ${SOURCE_FILES})

# add subdirectory glm GLAD GLFW 
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/glfw)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/glad)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/assimp)

# link libaries
target_link_libraries(${CMAKE_PROJECT_NAME} glad glfw OpenGL::GL assimp)