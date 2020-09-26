#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "generator.h"
#include "window.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

square::square(shader* p, window* win) {
	win_ptr = win;
	prog_ptr = p;
	prog_ptr->use();
	// basic 1x1 square model
	init_buff();
	// atr_ptrs
	set_attr();
	init_trans();
	// unbind
	unbind();
	prog_ptr->unbind();
}
square::square() {
}
void square::bind() {
	bind_tex();
	glBindVertexArray(vao);
}
void square::unbind() {
	glBindVertexArray(0);
}
// private
// set attr pointers
void square::set_attr() {
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
// init buffers
void square::init_buff() {
	float vertices[] = {
		0.5f,  0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
		0.5f,  0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
	};
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// vbo
	uint32_t vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}
// init transform matrices
void square::init_trans() {
	// model mat
	model = glm::mat4(1.0f);
	// perspective mat
	float aspect = win_ptr->w / win_ptr->h;
	proj = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
	// attatch
	int model_loc = glGetUniformLocation(prog_ptr->p_id, "model");
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
	// attatch
	int proj_loc = glGetUniformLocation(prog_ptr->p_id, "projection");
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(proj));
}
// optional texture
// bind texture buffer
void square::bind_tex() {
	glBindTexture(GL_TEXTURE_2D, tex_id);
}
// load a texture buffer
void square::load_texture(const char* path) {
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	// texture buffer
	glGenTextures(1, &tex_id);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	// set the texture wrapping/filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// generate using image data
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "FAILED TO LOAD TEXTURE" << std::endl;
	}
	stbi_image_free(data);
}
