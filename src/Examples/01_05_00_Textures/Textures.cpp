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
#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"

using namespace std;
using namespace Hdgbdn;
namespace fs = std::filesystem;

// settings
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;
const string APP_NAME = "Textures";

int main(int, char**)
{

	cout << APP_NAME << endl;
	Window window(SCR_WIDTH, SCR_HEIGHT, APP_NAME);

    const fs::path shader_path = fs::current_path().parent_path() / "Shaders";
    Shader shader((shader_path / "vertex.vs").string(), (shader_path / "fragment.fs").string());

    const fs::path texture_path = fs::current_path().parent_path().parent_path() / "res"/ "textures";

    glm::vec3 clear_color(0.2f, 0.3f, 0.3f);
    float mix_ration = 0.2f;

    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Texture tex_1((texture_path / "wall.jpg").string().c_str());
    Texture tex_2((texture_path / "wood.png").string().c_str());
	
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0* sizeof(float)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

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
            shader.set("tex_1", 0);
            shader.set("tex_2", 1);
            shader.set("ratio", mix_ration);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, tex_1.GetID());
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, tex_2.GetID());
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
                ImGui::SliderFloat("mix ratio", &mix_ration, 0.0f, 1.0f);
				ImGui::End();
			}
            // render ui on the top
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        });
    auto endOp = new LambdaOp([&]()
        {
			glfwSwapBuffers(window.GetWindow());
        });
    auto opQueue = new OpQueue;
    (*opQueue) << initOp << eventOp << renderOp << uiOp << endOp;
    window.Run(opQueue);

	return 0;
}
