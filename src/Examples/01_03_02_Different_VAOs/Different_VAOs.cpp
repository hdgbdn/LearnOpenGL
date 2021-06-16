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

    float vertices_1[] = {
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    };
	
    float vertices_2[] = {
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
    };

    // 1.generate buffer and data object
    unsigned int VAO_1, VBO_1;
    glGenVertexArrays(1, &VAO_1);
    glGenBuffers(1, &VBO_1);
	// 1.1 bind VAO at first
    glBindVertexArray(VAO_1);
	// 2.bind our VBO to array buffer, and copy vertices into a vertex buffer for OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO_1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);
	// 4.set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int VAO_2, VBO_2;
    glGenVertexArrays(1, &VAO_2);
    glGenBuffers(1, &VBO_2);
    glBindVertexArray(VAO_2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_2), vertices_2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	// unbind buffers and VAO
    glBindVertexArray(0);

    const fs::path shader_path = fs::current_path().parent_path() / "Shaders";
    Shader shader((shader_path / "vertex.vs").string(), (shader_path / "fragment.fs").string());

	auto renderOp = new LambdaOp([&]()
		{
            glfwPollEvents();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
			{
				static float f = 0.0f;
				static int counter = 0;

				ImGui::Begin(APP_NAME.c_str()); // Create a window called "Hello, world!" and append into it.

				
				ImGui::End();
			}

			// Rendering
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
            shader.Use();
            glBindVertexArray(VAO_1);
			glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(VAO_2);
			glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			glfwSwapBuffers(window.GetWindow());
		});
    auto opQueue = new OpQueue;
    (*opQueue) << renderOp;
    window.Run(opQueue);

	return 0;
}
