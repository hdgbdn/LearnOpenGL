#include <iostream>
#include "glad/glad.h"
#include "Window.h"
#include "Input.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Operation.h"
#include "Shader.h"

using namespace std;
using namespace hdgbdn;
namespace fs = std::filesystem;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const string APP_NAME = "Draw Two Triangle";

const fs::path shader_path = fs::current_path().parent_path() / "Shaders";

int main()
{
    cout << APP_NAME << endl;
    Window window(SCR_WIDTH, SCR_HEIGHT, APP_NAME);
    Input input(window);

    VAO vao = { 3 };
    VBO vbo({
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
        });
    EBO ebo({
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
        });

    VAO::Bind(vao);
    vbo.BufferData();
    ebo.BufferData();
    VAO::SetAttrPointer(vao);
    VAO::UnBind();

    Shader shader((shader_path / "vertex.vs").string(), (shader_path / "fragment.fs").string());

    window.PushRenderOperation(Operation([&]
        {
            glfwPollEvents();
            input.Update();
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader.Use();

            VAO::Bind(vao);
            ebo.Draw();
            glfwSwapBuffers(window);
        }));
    window.PushPostRenderOperation(Operation([]()
        {
            glfwTerminate();
        }));

    input.SetKeyDownCb(GLFW_KEY_ESCAPE, Operation([&window]()
        {
            window.Close();
        }));

    Window::StartRenderLoop(window);
    return 0;
}