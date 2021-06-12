macro(ADD_SUB_EXAMPLE TARGET_NAME TARGET_SOURCES TARGET_LIBS)
    add_executable(${TARGET_NAME} ${TARGET_SOURCES})
    target_link_libraries(${TARGET_NAME} PUBLIC 
            ${TARGET_LIBS})
    set_target_properties(${TARGET_NAME} PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF
            )
endmacro(ADD_SUB_EXAMPLE TARGET_NAME TARGET_SOURCES)

macro(ADD_ALLSUBDIR)
    file(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
    foreach(child ${children})
        if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${child})
            add_subdirectory(${child})
        endif()
    endforeach()
endmacro(ADD_ALLSUBDIR)

cmake_minimum_required(VERSION 3.10)
project(LearnOpenGL)

# find packages
find_package(OpenGL REQUIRED)

# add subdirectory glm GLAD GLFW 
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/3rd/glfw)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/3rd/glad)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/3rd/assimp)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/3rd/glm)

# add examples
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/Examples)

# libs #
## Learn OpenGL lib ##
file(GLOB LOPGL_SRC
    "src/LOPGL/*.cpp"
)
add_library(LOPGL STATIC
    ${LOPGL_SRC}
)
target_include_directories(LOPGL 
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/LOPGL
    )
target_link_libraries(LOPGL glad glfw OpenGL::GL assimp glm::glm)

## My personal utils
file(GLOB HDGBDN_SRC
     "src/Utility/*.cpp"
)
add_library(HDGBDN STATIC
    ${HDGBDN_SRC}
)
target_include_directories(HDGBDN 
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include/Utility
)
target_link_libraries(HDGBDN glad glfw)

set_target_properties(HDGBDN PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF
            )

# an old build
add_executable("hdr" src/hdr.cpp)
target_link_libraries("hdr" glad glfw OpenGL::GL assimp glm::glm LOPGL HDGBDN)

# add sub example targets

# add libraies

# link example targets and libraies