#include <iostream>
#include "glad/glad.h"
#include "Window.h"
#include "Input.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Operation.h"
#include "Shader.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace std;
using namespace hdgbdn;
namespace fs = std::filesystem;

// settings
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;
const string APP_NAME = "Different colors";

const fs::path shader_path = fs::current_path().parent_path() / "Shaders";

int main(int, char**)
{

	cout << APP_NAME << endl;
	Window window(SCR_WIDTH, SCR_HEIGHT, APP_NAME);
	Input input(window);

    VAO vao1{ 3 };
	VBO vbo1({
		0.5f,  0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		}, 3);
	VAO::Bind(vao1);
	vbo1.BufferData();
	VAO::SetAttrPointer(vao1);
	VAO::UnBind();

	VAO vao2{ 3 };
	VBO vbo2({
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
		0.5f,  0.5f, 0.0f,
		}, 3);
	VAO::Bind(vao2);
	vbo2.BufferData();
	VAO::SetAttrPointer(vao2);
	VAO::UnBind();
	
    Shader shader((shader_path / "vertex.vs").string(), (shader_path / "fragment.fs").string());
    Shader shader_2((shader_path / "vertex.vs").string(), (shader_path / "fragment_yellow.fs").string());

	glm::vec3 color1(0.f, 1.f, 0.f);
	glm::vec3 color2(1.f, 0.f, 0.f);
	
	window.PushPreRenderOperation(Operation([&window]()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		(void)io;

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		ImGui::GetFontSize();
		style.ScaleAllSizes(2);

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 130");
	}));
	
	window.PushRenderOperation(Operation([&]
		{
			glfwPollEvents();
			input.Update();
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			shader.Use();
			shader.set("color", color1);
			VAO::Bind(vao1);
			vbo1.Draw();

			shader_2.Use();
			shader_2.set("color", color2);
			VAO::Bind(vao2);
			vbo2.Draw();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			{
				ImGui::Begin(APP_NAME.c_str());
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::ColorEdit3("color1", (float*)&color1);
				ImGui::ColorEdit3("color2", (float*)&color2);
				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
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
