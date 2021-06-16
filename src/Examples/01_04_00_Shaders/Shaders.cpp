#include <stdio.h>
#include <string>
#include <filesystem>
#include <iostream>
#include "Window.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "LambdaOp.h"
#include "OpQueue.h"
#include "Shader.h"

using namespace std;
using namespace Hdgbdn;
namespace fs = std::filesystem;

// settings
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;
const string APP_NAME = "Shaders";

int main(int, char**)
{

	cout << APP_NAME << endl;
	Window window(SCR_WIDTH, SCR_HEIGHT, APP_NAME);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    const fs::path shader_path = fs::current_path().parent_path() / "Shaders";
    Shader shader((shader_path / "vertex.vs").string(), (shader_path / "fragment.fs").string());

    glm::vec3 clear_color(0.2f, 0.3f, 0.3f);

    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };
    
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
	// 2.bind our VBO to array buffer, and copy vertices into a vertex buffer for OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 4.set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0* sizeof(float)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    auto initOp = new LambdaOp([&]()
        {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            (void)io;

            ImGui::StyleColorsDark();

            ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);
            ImGui_ImplOpenGL3_Init("#version 130");
        }, false);

    auto eventOp = new LambdaOp([&]()
        {
            glfwPollEvents();
        });

	auto renderOp = new LambdaOp([&]()
		{
            glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
            shader.Use();
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);
		});

    auto uiOp = new LambdaOp([&]()
        {
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			{
				ImGui::Begin(APP_NAME.c_str());
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::ColorEdit3("clear color", (float*)&clear_color);
				ImGui::End();
			}
            // render ui on the top
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        });
    auto swapBufOp = new LambdaOp([&]()
        {
			glfwSwapBuffers(window.GetWindow());
        });
    auto opQueue = new OpQueue;
    (*opQueue) << initOp << eventOp << renderOp << uiOp << swapBufOp;
    window.Run(opQueue);

	return 0;
}
