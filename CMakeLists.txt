cmake_minimum_required(VERSION 3.3)
project(LearnOpenGL)

# find packages
find_package(OpenGL REQUIRED)

# include
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

# add subdirectory GLAD GLFW
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/glad)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/glfw)

# execute
set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src/)
set(SOURCE_FILES main.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})


# link libaries
target_link_libraries(${CMAKE_PROJECT_NAME} glad glfw OpenGL::GL)
