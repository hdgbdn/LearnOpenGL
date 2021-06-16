#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include "Window.h"
#include "LambdaOp.h"
#include "OpQueue.h"
#include "EventMgr.h"
#include "Shader.h"
#include <iostream>

using namespace std;
using namespace Hdgbdn;
namespace fs = std::filesystem;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const string APP_NAME = "Hello Triangle";


int main()
{
    cout << APP_NAME << endl;
    Window window(SCR_WIDTH, SCR_HEIGHT, APP_NAME);

    float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // 1.generate buffer and data object
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
	// 1.1 bind VAO at first
    glBindVertexArray(VAO);
	// 2.bind our VBO to array buffer, and copy vertices into a vertex buffer for OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.bind our EBO to element buffer,copy index array into a element buffer for OpenGL
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 4.set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	// unbind buffers and VAO
    glBindVertexArray(0);

    const fs::path shader_path = fs::current_path().parent_path() / "Shaders";

    Shader shader((shader_path / "vertex.vs").string(), (shader_path / "fragment.fs").string());

    auto initOp = new LambdaOp([&]()
        {
            EventMgr::GetInstance()->SetKeyPress(GLFW_KEY_ESCAPE, new LambdaOp([&]()
                {
                    window.CloseWindow();
                }));
        }
    , false);
    auto renderOp = new LambdaOp([&]()
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            shader.Use();
    		// now the VAO stored EBO and VBO, so binding VAO, the EBO and VBO are also being bond
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
            glfwSwapBuffers(window.GetWindow());
            glfwPollEvents();
        });

    auto endOp = new LambdaOp([&]()
        {
        });
    auto opQueue = new OpQueue;
    (*opQueue) << initOp << renderOp << endOp;
    window.Run(opQueue);
    return 0;
}