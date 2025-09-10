#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "VertexArrayObject.h"

#include <string>

class Application
{
public:
	Application(const char* windowName);

	void run();
private:
	// inits
	bool init();
	bool initGLFW();
	bool initGLAD();
	bool initImGui();



private:
	// opengl
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow* window);

	void render();


	GLFWwindow* m_window = nullptr;
	const char* m_windowName = nullptr;

	
    // imgui
    void beginImguiFrame();
    
    ImGuiIO* m_imguiIO = nullptr;


    // app variables
	bool m_renderWireframe = false;




    std::string loadShaderSource(const std::string& pathToShader);
};