#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "window.h"
#include "generator.h"
#include "shader.h"
#include "camera.h"

int main() {
	// map
	map tile_map = map("grid.txt");
	tile_map.find_wall_pos();
	window win = window("Test");
	// wall
	shader wall_shader = shader("./shaders/wallv_shader.txt", "./shaders/wallf_shader.txt");
	// floor
	shader floor_shader = shader("./shaders/tilev_shader.txt", "./shaders/tilef_shader.txt");
	wall seg_buf = wall(&wall_shader, &win);
	tile tile_buf = tile(&floor_shader, &win);
	// cam
	camera cam = camera(&win, &tile_map.cam_pos);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(win.ptr)) {
		win.handle_input();
		win.update_time();
		cam.update();
		// draw
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		seg_buf.draw_walls(&tile_map, &cam);
		tile_buf.draw_floors(&tile_map, &cam);
		glfwPollEvents();
		glfwSwapBuffers(win.ptr);
	}
}
