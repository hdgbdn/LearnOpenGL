#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Model.h"
#include "CommonHeader.h"
namespace fs = std::filesystem;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

unsigned int loadCubemap(vector<string> faces);
vector<std::string> faces
{
    "right.jpg",
        "left.jpg",
        "top.jpg",
        "bottom.jpg",
        "front.jpg",
        "back.jpg"
};
// settings
unsigned int SCR_WIDTH = 1024;
unsigned int SCR_HEIGHT = 1024;

const fs::path shader_floder(fs::current_path().parent_path().parent_path() /"shaders");

const std::string v_shader_name = "simple_vertex.vs";
const std::string f_shader_name = "simple_fragment.fs";

const std::string v_outline_name = "outline.vs";
const std::string f_outline_name = "outline.fs";

Camera camera(glm::vec3(1.0f, 0.0f, 6.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool viewMode = false;
bool needReloadShader = false;
// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

void DrawCube(Shader& shader)
{
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    shader.Use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    shader.SetMVP(model, view, projection);
    cube.Draw(shader);
}

void DrawPlane(Shader& shader)
{

    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    shader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 2.0f));
    shader.SetMVP(model, view, projection);
    plane.Draw(shader);
}

void DrawSkyBox(Shader& shader)
{
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
    shader.set("projection", projection);
    shader.set("view", view);
    shader.set("skybox", 0);
    meshSkybox.Draw(shader);
}


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, NULL);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    vector<Shader> shaders;
    fs::path v_path = shader_floder / v_shader_name;
    fs::path f_path = shader_floder / f_shader_name;
    Shader shader(v_path.string(), f_path.string());
    shaders.push_back(shader);
    fs::path v_ol_path = shader_floder / v_outline_name;
    fs::path f_ol_path = shader_floder / f_outline_name;
    Shader outline(v_ol_path.string(), f_ol_path.string());
    shaders.push_back(outline);
    Shader screenShader((shader_floder / "frame_buffer.vs").string(), (shader_floder / "frame_buffer.fs").string());
    shaders.push_back(screenShader);
    Shader skybox((shader_floder / "skybox.vs").string(), (shader_floder / "skybox.fs").string());
	shaders.push_back(skybox);
	Shader reflection((shader_floder / "reflection.vs").string(), (shader_floder / "reflection.fs").string());
    shaders.push_back(reflection);
    Shader geo((shader_floder / "explode.vs").string(), (shader_floder / "explode.fs").string(), (shader_floder / "explode.gs").string());
    shaders.push_back(geo);
	fs::path test_model_path(fs::current_path().parent_path().parent_path() /"res"/"model"/"pony-car"/"source"/"Pony_cartoon.obj");
    Model test_model(test_model_path.string().c_str());

    SetDefaultMesh();

	// geo shader object
    float points[] = {
    -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // top-right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
    -0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // bottom-left
    };
    unsigned VAO, VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2*sizeof(float)));
    glBindVertexArray(0);
	// create skybox
    unsigned int cubemapTexture = loadCubemap(faces);

	// using uniform buffers
    unsigned int ubo;
    glGenBuffers(1, &ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, 2 * sizeof(glm::mat4));

    unsigned int uniformBlockSimple = glGetUniformBlockIndex(shader.ID, "Matrices");
    unsigned int uniformBlockSkybox = glGetUniformBlockIndex(skybox.ID, "Matrices");

    glUniformBlockBinding(shader.ID, uniformBlockSimple, 0);
    glUniformBlockBinding(skybox.ID, uniformBlockSkybox, 0);
	
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
    	
        if (needReloadShader)
        {
            for (auto s : shaders) s.Reload();
            needReloadShader = false;
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    	
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glBindBuffer(GL_UNIFORM_BUFFER, ubo);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        shader.Use();
        shader.set("model", glm::scale(glm::mat4(1.0f), glm::vec3(0.01f, 0.01f, 0.01f)));
        test_model.Draw(shader);
        geo.Use();
        geo.set("time", (float)glfwGetTime());
        geo.set("model", glm::scale(glm::mat4(1.0f), glm::vec3(0.01f, 0.01f, 0.01f)));
        test_model.Draw(geo);
    	
        glDepthMask(GL_FALSE);
        glDepthFunc(GL_LEQUAL);
        skybox.Use();
        skybox.set("skybox", 0);
        meshSkybox.Draw(skybox);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);
    	
        void* ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        // make sure to tell OpenGL we're done with the pointer
        glUnmapBuffer(GL_ARRAY_BUFFER);
    	
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
        needReloadShader = true;
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
        viewMode = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }

    else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE){
        viewMode = false;
        firstMouse = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(!viewMode) return;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

unsigned int loadCubemap(vector<string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    int width, height, nrChannels;
	for(unsigned int i = 0; i < faces.size(); i++)
	{
        fs::path skyboxPath = fs::current_path().parent_path().parent_path()/"res"/"textures"/"skybox2";
        unsigned char* data = stbi_load((skyboxPath/faces[i]).string().c_str(), &width, &height, &nrChannels, 0);
		if(data)
		{
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
		}
        else{
            std::cout << "ERROR::STBI::LOAD_IMAGE_FAILED" << std::endl;
            stbi_image_free(data);
		}
	}
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}