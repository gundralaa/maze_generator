#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "generator.h"
#include "window.h"
#include "camera.h"
#include <iostream>


wall::wall(shader* p, window* win) {
	load_texture("container.jpg");
	win_ptr = win;
	prog_ptr = p;
	prog_ptr->use();
	init_buff();
	// atr_ptrs
	set_attr();
	init_trans();
	std::cout << vao << std::endl;
	// unbind
	unbind();
	prog_ptr->unbind();
}
void wall::set_attr() {
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
}
void wall::init_buff() {
	float vertices[] = {
		0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	};
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// vbo
	uint32_t vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}
void wall::draw_walls(map* m, camera* cam) {
	prog_ptr->use();
	cam->set_view(prog_ptr);
	bind();
	for (int i = 0; i < m->wall_list.size(); ++i) {
		model = glm::mat4(1.0f);
		model = glm::translate(model, m->wall_list[i]);
		model = glm::rotate(model, glm::radians(90.0f) * m->rotate_list[i],
			glm::vec3(0.0f, 1.0f, 0.0f));
		int model_loc = glGetUniformLocation(prog_ptr->p_id, "model");
		glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	unbind();
	prog_ptr->unbind();
}

void tile::draw_floors(map* m, camera* cam) {
	prog_ptr->use();
	cam->set_view(prog_ptr);
	bind();
	for (int i = 0; i < m->floor_list.size(); ++i) {
		model = glm::mat4(1.0f);
		model = glm::translate(model, m->floor_list[i]);
		model = glm::rotate(model, glm::radians(90.0f),
			glm::vec3(1.0f, 0.0f, 0.0f));
		int model_loc = glGetUniformLocation(prog_ptr->p_id, "model");
		glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	unbind();
	prog_ptr->unbind();
}
