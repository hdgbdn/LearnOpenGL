#include <iostream>
#include "glad/glad.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Window.h"
#include "Input.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Operation.h"
#include "Shader.h"
#include "Texture.h"

using namespace std;
using namespace hdgbdn;
namespace fs = std::filesystem;

// settings
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;
const string APP_NAME = "Center pixel";
const fs::path shader_path = fs::current_path().parent_path() / "Shaders";
const fs::path res_path = fs::current_path().parent_path().parent_path() / "res";
const fs::path tex_path = res_path / "textures";

int main(int, char**)
{
	cout << APP_NAME << endl;
	Window window(SCR_WIDTH, SCR_HEIGHT, APP_NAME);
	Input input(window);

	Shader shader((shader_path / "vertex.vs").string(), (shader_path / "fragment.fs").string());

	glm::vec4 clear_color(0.2f, 0.3f, 0.3f, 1.0f);
	float ratio = .0f;

	VAO vao1{ 3, 3, 2 };
	VBO vbo1({
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.55f, 0.55f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.55f, 0.45f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.45f, 0.45f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.45f, 0.55f  // top left 
		}, 4);
	EBO ebo1({
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	});
	VAO::Bind(vao1);
	vbo1.BufferData();
	ebo1.BufferData();
	VAO::SetAttrPointer(vao1);
	VAO::UnBind();

	Texture tex1 = Texture((tex_path / "smile.jpg").string(), true, GL_CLAMP_TO_EDGE, GL_NEAREST);
	Texture tex2 = Texture((tex_path / "wood.png").string());

	window.PushPreRenderOperation(Operation([&]()
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

			shader.Use();
			shader.set("tex_1", 0);
			shader.set("tex_2", 1);
		}));

	window.PushRenderOperation(Operation([&]
		{
			glfwPollEvents();
			input.Update();
			glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
			glClear(GL_COLOR_BUFFER_BIT);

			shader.Use();
			shader.set("ratio", ratio);
			Texture::BindToUnit(tex1, 0);
			Texture::BindToUnit(tex2, 1);
			VAO::Bind(vao1);
			ebo1.Draw();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			{
				ImGui::Begin(APP_NAME.c_str());
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::ColorEdit4("Clear color", (float*)&clear_color);
				ImGui::SliderFloat("Blend ratio", &ratio, .0f, 1.f);
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
