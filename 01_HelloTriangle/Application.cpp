#include "Application.h"
#include "Logger.hpp"


#include <string>
#include <fstream>
#include <ostream>


// opengl
#include "VertexBufferObject.h"
#include "ShaderProgram.h"
#include "VertexArrayObject.h"
#include "ElementBufferObject.h"
#include "VertexBufferLayout.h"

#include "Debug.h"

Application::Application(const char* windowName)
    : m_windowName(windowName)  {}

void Application::run()
{
    if (!init())
    {
        LOG_FATAL << "Failed to initialise application";
        return;
    }
    LOG_INFO << "Successfully initialised application";




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





    VertexBufferObject vbo(vertices, sizeof(vertices));
    VertexArrayObject vao;

    ElementBufferObject ebo(indices, sizeof(indices));

    ShaderProgram shaderProgram("deps/shaders/vertex.shader", "deps/shaders/fragment.shader");
    


    VertexBufferLayout vboLayout;
    vboLayout.push<float>(3);

    vao.bind();
    vbo.bind();
    ebo.bind();

    vao.addBuffer(vbo, vboLayout);



    shaderProgram.use();


    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    while (!glfwWindowShouldClose(m_window))
    {
        beginImguiFrame();
        processInput(m_window);

        render();

          


        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }


    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return;
}

void Application::render()
{
    if (m_renderWireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);




    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


// opengl
void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Application::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


// inits
bool Application::init()
{
    if (!initGLFW()) return false;
    if (!initGLAD()) return false;
    if (!initImGui()) return false;

    return true;
}



bool Application::initGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_window = glfwCreateWindow(2400, 1800, m_windowName, NULL, NULL);
    if (m_window == NULL)
    {
        LOG_FATAL << "Failed Creating GLFW Window";
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(m_window);
    LOG_INFO << "Created GLFW Window";


    return true;
}

bool Application::initGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_FATAL << "Failed to load GLAD";
        return false;
    }

    LOG_INFO << "Loaded GLAD";
    return true;
}

bool Application::initImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& m_imguiIO = ImGui::GetIO(); (void)m_imguiIO;

    const char* imguiFontPath = "deps/fonts/Roboto-Medium.ttf";

    if (!std::ifstream(imguiFontPath).good())
    {
        LOG_FATAL << "Imgui Font file cannot be found: " << imguiFontPath;
        return false;
    }
    LOG_INFO << "Loaded Imgui Font file: " << imguiFontPath;

    m_imguiIO.Fonts->AddFontFromFileTTF(imguiFontPath, 34.f);
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    return true;
}


// imgui
void Application::beginImguiFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Control Panel");
    ImGui::Checkbox("Wireframe", &m_renderWireframe);

    ImGui::End();
}




std::string Application::loadShaderSource(const std::string& pathToShader)
{
    std::ifstream file(pathToShader, std::ios::in | std::ios::binary);
    if (!file)
    {
        LOG_FATAL << "Failed to load shader: " << pathToShader;
        return "";
    }

    std::ostringstream contents;
    contents << file.rdbuf();
    return contents.str();
}