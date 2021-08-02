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
#include "Camera.h"
#include "Color.h"
#include "Light.h"
#include "LightHelper.h"

using namespace std;
using namespace hdgbdn;
namespace fs = std::filesystem;

// settings
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;
const string APP_NAME = "Light cast";
const fs::path shader_path = fs::current_path().parent_path() / "Shaders";
const fs::path res_path = fs::current_path().parent_path().parent_path() / "res";
const fs::path font_path = res_path / "Fonts";
const fs::path tex_path = res_path / "textures";

const int PointLightNums = 4;

int main(int, char**)
{
	cout << APP_NAME << endl;
	Window window(SCR_WIDTH, SCR_HEIGHT, APP_NAME);
	Input input(window);
	Camera cam = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	DirectionalLight dirLight;
	vector<PointLight> pointLights;
	pointLights.push_back(PointLight(glm::vec3(-1.f, -1.f, 0.f)));
	pointLights.push_back(PointLight(glm::vec3(1.f, -1.f, 0.f)));
	pointLights.push_back(PointLight(glm::vec3(-1.f, 1.f, 0.f)));
	pointLights.push_back(PointLight(glm::vec3(1.f, 1.f, 0.f)));

	Shader lightShader((shader_path / "lightCube.vs").string(), (shader_path / "lightCube.fs").string());
	Shader colorShader((shader_path / "light.vs").string(), (shader_path / "light.fs").string());

	glm::vec4 clear_color(0.2f, 0.3f, 0.3f, 1.0f);

	glm::vec3 colorPos(0.f, 0.f, -.5f);
	glm::vec3 rotate_axis(1.0f, .0f, .0f);
	float rotate_angle = .0f;

	// light arguments
	float materialShininess(32.f);


	VAO vao1{3, 3, 2};
	VBO vbo1({
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
		}, 36);
	VAO::Bind(vao1);
	vbo1.BufferData();
	VAO::SetAttrPointer(vao1);
	VAO::UnBind();
	
	Texture texDiffuse = Texture((tex_path / "container2.png").string());
	Texture texSpecular = Texture((tex_path / "container2_specular.png").string());

	window.PushPreRenderOperation(Operation([&]()
		{
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			io.Fonts->AddFontFromFileTTF((font_path/"sarasa-term-j-regular.ttf").string().c_str(), 20);

			ImGui::StyleColorsDark();

			ImGuiStyle& style = ImGui::GetStyle();
	
			style.ScaleAllSizes(1.5);

			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 130");

			colorShader.Use();
			colorShader.set("material.diffuse", 0);
			colorShader.set("material.specular", 1);

			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}));

	window.PushRenderOperation(Operation([&]
		{
			glfwPollEvents();
			input.Update();

			glEnable(GL_DEPTH_TEST);
			glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			glm::mat4 view = cam.GetViewMatrix();

			glm::mat4 projection = glm::perspective(glm::radians(cam.GetZoom()), (float)window.GetWidth() / (float)window.GetHeight(), 0.1f, 100.0f);
		
			lightShader.Use();
			VAO::Bind(vao1);

			for(int i = 0; i < PointLightNums; i++)
			{
				lightShader.set("light.position", pointLights[i].getPosition());
				lightShader.set("light.ambient", pointLights[i].getColor());
				lightShader.set("light.diffuse", pointLights[i].getColor());
				lightShader.set("light.specular", pointLights[i].getColor());
				glm::mat4 lightModel = glm::translate(glm::mat4(1.0f), pointLights[i].getPosition());
				lightShader.set("model", lightModel);
				lightShader.set("view", view);
				lightShader.set("projection", projection);
				vbo1.Draw();
			}


			glm::mat4 colorModel = glm::mat4(1.0f);
			colorModel = glm::translate(colorModel, glm::vec3(colorPos));
			colorModel = glm::rotate(colorModel, glm::radians(rotate_angle), rotate_axis);
			colorShader.Use();
			SetDirectLight(colorShader, dirLight);
			for (int i = 0; i < PointLightNums; i++) SetPointLight(colorShader, pointLights[i], i);
			colorShader.set("viewPos", cam.GetPosition());

			colorShader.set("material.shininess", materialShininess);
			colorShader.set("model", colorModel);
			colorShader.set("view", view);
			colorShader.set("projection", projection);
			Texture::BindToUnit(texDiffuse, 0);
			Texture::BindToUnit(texSpecular, 1);
			VAO::Bind(vao1);
			vbo1.Draw();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			{
				ImGui::Begin(APP_NAME.c_str());
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::ColorEdit4("Clear color", (float*)&clear_color);
				ImGui::SliderFloat3("Rotate Axis", reinterpret_cast<float*>(&rotate_axis), -1.f, 1.f);
				ImGui::SliderFloat("Rotate angle", &rotate_angle, 0.0f, 128.f);
				ImGui::SliderFloat("Material shininess", &materialShininess, 0.0f, 128.f);

				if (ImGui::CollapsingHeader("Directional light"))
				{
					ImGui::ColorEdit3("Directional light color", (float*)dirLight.getColorRaw());
					ImGui::SliderFloat("Directional light ambient", dirLight.getAmbientRaw(), 0.0f, 1.f);
					ImGui::SliderFloat("Directional light diffuse", dirLight.getDiffuseRaw(), 0.0f, 1.f);
					ImGui::SliderFloat("Directional light specular", dirLight.getSpecularRaw(), 0.0f, 1.f);
					ImGui::SliderFloat3("Directional light position", (float*)dirLight.getPositionRaw(), -2.f, 2.f);
					ImGui::SliderFloat3("Directional light direction", (float*)dirLight.getDirectionRaw(), -1.f, 1.f);
				}

				if (ImGui::CollapsingHeader("Point light"))
				{
					for(int i = 0; i < PointLightNums; i++)
					{
						string label = "Point light " + to_string(i);
						ImGui::SliderFloat3((label + " Position").c_str(), (float*)pointLights[i].getPositionRaw(), -2.f, 2.f);
						ImGui::ColorEdit3((label + " Color").c_str(), (float*)pointLights[i].getColorRaw());
						ImGui::SliderFloat((label + " ambient").c_str(), pointLights[i].getAmbientRaw(), 0.0f, 1.f);
						ImGui::SliderFloat((label + " diffuse").c_str(), pointLights[i].getDiffuseRaw(), 0.0f, 1.f);
						ImGui::SliderFloat((label + " specular").c_str(), pointLights[i].getSpecularRaw(), 0.0f, 1.f);
						ImGui::SliderFloat((label + " KC").c_str(), (float*)pointLights[i].getKCraw(), 0.f, 1.f);
						ImGui::SliderFloat((label + " KL").c_str(), (float*)pointLights[i].getKLraw(), 0.f, 2.f);
						ImGui::SliderFloat((label + " KQ").c_str(), (float*)pointLights[i].getKQraw(), 0.f, 2.f);
					}
				}

				ImGui::Text("Camera: Position x:%.3f, y:%.3f, z:%.3f", cam.GetPosition().x, cam.GetPosition().y, cam.GetPosition().z);
				ImGui::Text("Mouse: Position x:%.3f, y:%.3f, Delta: x:%.3f, y:%.3f", input.GetCursorPos().x, input.GetCursorPos().y, input.GetCursorDelta().x, input.GetCursorDelta().y);
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
	input.SetKeyDownCb(GLFW_KEY_W, Operation([&cam, &input]
		{
			cam.Move(Camera_Movement::FORWARD, input.GetDelta());
		}));
	input.SetKeyDownCb(GLFW_KEY_A, Operation([&cam, &input]
		{
			cam.Move(Camera_Movement::LEFT, input.GetDelta());
		}));
	input.SetKeyDownCb(GLFW_KEY_D, Operation([&cam, &input]
		{
			cam.Move(Camera_Movement::RIGHT, input.GetDelta());
		}));
	input.SetKeyDownCb(GLFW_KEY_S, Operation([&cam, &input]
		{
			cam.Move(Camera_Movement::BACKWARD, input.GetDelta());
		}));
	input.SetKeyDownCb(GLFW_MOUSE_BUTTON_RIGHT, Operation([&cam, &input]
		{
			input.DisableCursor();
			cam.SetControlMode(Camera_Control_Mode::FREE);
		}));
	input.SetKeyReleaseCb(GLFW_MOUSE_BUTTON_RIGHT, Operation([&cam, &input]
		{
			input.ShowCursor();
			cam.SetControlMode(Camera_Control_Mode::NONE);
		}));
	
	input.SetCursorPosCb([&cam, &window](double x, double y, double deltax, double deltay)
		{
			cam.RotateByMouse(deltax, deltay);
		});

	Window::StartRenderLoop(window);

	return 0;
}
