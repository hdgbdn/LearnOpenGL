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


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const string APP_NAME = "Hello Triangle";


int main()
{
    cout << APP_NAME << endl;
    Window window(SCR_WIDTH, SCR_HEIGHT, APP_NAME);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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
            glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
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