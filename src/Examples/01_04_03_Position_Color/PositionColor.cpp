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
const string APP_NAME = "Position Color";
const fs::path shader_path = fs::current_path().parent_path() / "Shaders";

int main(int, char**)
{
	cout << APP_NAME << endl;
	Window window(SCR_WIDTH, SCR_HEIGHT, APP_NAME);
	Input input(window);

	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	Shader shader((shader_path / "vertex.vs").string(), (shader_path / "fragment.fs").string());

	glm::vec4 clear_color(0.2f, 0.3f, 0.3f, 1.0f);
	glm::vec3 offset(.0f, .0f, .0f);

	VAO vao1{ 3, 3 };
	VBO vbo1{
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};
	VAO::Bind(vao1);
	vbo1.BufferData();
	VAO::SetAttrPointer(vao1);
	VAO::UnBind();

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
			glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
			glClear(GL_COLOR_BUFFER_BIT);

			shader.Use();
			shader.set("offset", offset);
			VAO::Bind(vao1);
			vbo1.Draw();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			{
				ImGui::Begin(APP_NAME.c_str());
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::ColorEdit4("Clear color", (float*)&clear_color);
				ImGui::SliderFloat3("Offset", (float*)&offset, -1.0f, 1.0f);
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
