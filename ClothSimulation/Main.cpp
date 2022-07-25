#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdio>
#include <string>
#include "Simulator.h"

#define GLFW_INCLUDE_GLCOREARB

void framebuffer_resize_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

GLFWwindow* initialize_window();


Simulator Sim(1920, 1080);

float lastX = 1920 / 2.0f;
float lastY = 1080/ 2.0f;
float fov = 45.0f;
bool firstMouse = true;

int main()
{
	// Go ahead and get information and init everything before window appears since we have to read from CLI

	GLFWwindow* window = initialize_window();
	if (!window)
		return -1;
	
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;


	Sim.initSystem();


	while (!glfwWindowShouldClose(window)) {
		// check and call events and swap the buffers
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Calculate Delta Time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		
		// Get Input
		Sim.ProcessInput(deltaTime);

		// Update Simulator
		Sim.Update(deltaTime);

		// Render Simulation
		Sim.Render();
		
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

// Create and Return Window Pointer
GLFWwindow* initialize_window()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(Sim.Width, Sim.Height, "Cloth Simulation", NULL, NULL);
	if (window == NULL) {
		std::cout << "Window creation failed" << std::endl;
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLAD Failed" << std::endl;
		return NULL;
	}
	glViewport(0, 0, 1920, 1080);
	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	std::cout << "GLFW INITIALIZED" << std::endl;
	return window;
}

// Callbacks
void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	// when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			Sim.Keys[key] = true;
		else if (action == GLFW_RELEASE)
			Sim.Keys[key] = false;
	}
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

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

	Sim.ProcessMouse(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Sim.ProcessScroll(static_cast<float>(yoffset));
}
