#include <stdio.h>
#include <string>
#include <filesystem>
#include <iostream>
#include "Window.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
#include "LambdaOp.h"
#include "OpQueue.h"
#include "Shader.h"

using namespace std;
using namespace Hdgbdn;
namespace fs = std::filesystem;

// settings
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;
const string APP_NAME = "Draw 2 Triangles";

int main(int, char**)
{

	cout << APP_NAME << endl;
	Window window(SCR_WIDTH, SCR_HEIGHT, APP_NAME);
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	ImGui::StyleColorsDark();
    
	ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 130");

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

	auto renderOp = new LambdaOp([&]()
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
			{
				static float f = 0.0f;
				static int counter = 0;

				ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

				
				ImGui::End();
			}

			// Rendering
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            shader.Use();
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
			glfwSwapBuffers(window.GetWindow());
		});
    auto opQueue = new OpQueue;
    (*opQueue) << renderOp;
    window.Run(opQueue);

	return 0;
}
