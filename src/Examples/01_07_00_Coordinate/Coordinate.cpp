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
const string APP_NAME = "Coordinate";
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
	
	glm::vec3 rotate_axis(1.0f, .0f, .0f);
	float rotate_angle = .0f;

	float view_distance = 3.0f;

	float fov = 45.f;
	float hw_ration = 1.f;

	VAO vao1{ 3, 2};
	VBO vbo1({
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		}, 36);
	VAO::Bind(vao1);
	vbo1.BufferData();
	VAO::SetAttrPointer(vao1);
	VAO::UnBind();

	Texture tex1 = Texture((tex_path / "smile.jpg").string(), true, GL_REPEAT, GL_NEAREST);
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

			glEnable(GL_DEPTH_TEST);
			glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::rotate(model, glm::radians(rotate_angle), rotate_axis);

			glm::mat4 view = glm::mat4(1.0f);
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -view_distance));

			glm::mat4 projection;
			projection = glm::perspective(glm::radians(fov), hw_ration, 0.1f, 100.0f);
		
			shader.Use();
			shader.set("ratio", ratio);
			shader.set("model", model);
			shader.set("view", view);
			shader.set("projection", projection);
			Texture::BindToUnit(tex1, 0);
			Texture::BindToUnit(tex2, 1);
			VAO::Bind(vao1);
			vbo1.Draw();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			{
				ImGui::Begin(APP_NAME.c_str());
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::ColorEdit4("Clear color", (float*)&clear_color);
				ImGui::SliderFloat("Blend ratio", &ratio, .0f, 1.f);
				ImGui::SliderFloat3("Rotate Axis", reinterpret_cast<float*>(&rotate_axis), -1.f, 1.f);
				ImGui::SliderFloat("Rotate Angle", &rotate_angle, -180.f, 180.f);
				ImGui::SliderFloat("View distance", &view_distance, -10.f, 10.f);
				ImGui::SliderFloat("Filed of view", &fov, 0.f, 120.f);
				ImGui::SliderFloat("Height width ration", &hw_ration, 1.f, 2.f);
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
