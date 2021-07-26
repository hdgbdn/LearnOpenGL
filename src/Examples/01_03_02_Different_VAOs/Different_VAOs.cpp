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
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;
const string APP_NAME = "Different VAOs";
const fs::path shader_path = fs::current_path().parent_path()/"Shaders";

int main(int, char**)
{
    cout << APP_NAME << endl;
    Window window(SCR_WIDTH, SCR_HEIGHT, APP_NAME);
    Input input(window);

    VAO vao1 = { 3 };
	VBO vbo1({
	 0.5f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
		}, 3);

    VAO::Bind(vao1);
    vbo1.BufferData();
    VAO::SetAttrPointer(vao1);
    VAO::UnBind();

    VAO vao2(vao1);
    VBO vbo2({
    -0.8f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
     0.5f,  0.7f, 0.0f,
        }, 3);
    VAO::Bind(vao2);
    vbo2.BufferData();
    VAO::SetAttrPointer(vao2);
    VAO::UnBind();

    Shader shader((shader_path / "vertex.vs").string(), (shader_path / "fragment.fs").string());

    window.PushRenderOperation(Operation([&]
        {
            glfwPollEvents();
            input.Update();
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader.Use();

            VAO::Bind(vao1);
            vbo1.Draw();
            VAO::Bind(vao2);
            vbo2.Draw();
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
