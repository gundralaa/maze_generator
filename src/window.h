#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class window {
public:
	GLFWwindow* ptr;
	float h = 600.0f;
	float w = 800.0f;
	float delta_time = 0.0f;
	window(int width, int height, const char* name);
	window(const char* name);
	void handle_input();
	void update_time();
private:
	float last_frame = 0.0f;
	void init(int width, int height, const char* name);
};

#endif

