#include "window.h"
#include <iostream>

void buff_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void window::init(int width, int height, const char* name) {
	// init glfw and set version 3.3
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// create window pointer
	ptr = glfwCreateWindow(width, height, name, NULL, NULL);
	if (ptr == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
	}
	// set opengl context
	glfwMakeContextCurrent(ptr);
	// load platform specific func pointers using GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to init GLAD (func pointer manager OpenGL" << std::endl;
	}
	// set viewport for gl manipulation
	glViewport(0, 0, width, height);
	// set callback
	glfwSetFramebufferSizeCallback(ptr, buff_callback);
}
void window::update_time() {
	float curr_frame = glfwGetTime();
	delta_time = curr_frame - last_frame;
	last_frame = curr_frame;
}
window::window(int width, int height, const char* name) {
	init(width, height, name);
}

window::window(const char* name) {
	init((int) w, (int) h, name);
}

void window::handle_input() {
	if (glfwGetKey(ptr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(ptr, true);
}