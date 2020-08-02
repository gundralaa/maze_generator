#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "generator.h"
#include "shader.h"

void shader::read_files(const char* v_path, const char* f_path) {
	reader v_file = reader(v_path);
	reader f_file = reader(f_path);
	v_code = v_file.str.c_str();
	f_code = f_file.str.c_str();
	init_program();
}
void shader::compile_shader(uint32_t id) {
	glCompileShader(id);
	int success;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << id << " FAILED SHADER COMPILATION\n" << infoLog << std::endl;
	}
	else {
		std::cout << id << " SHADER COMPILED" << std::endl;
	}
}
void shader::use() { 
	glUseProgram(p_id);
}
void shader::unbind() {
	glUseProgram(0);
}
void shader::init_program() {
	uint32_t v, f;
	// vertex
	v = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(v, 1, &v_code, NULL);
	// fragment
	f = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(f, 1, &f_code, NULL);
	// compile
	compile_shader(v);
	compile_shader(f);
	// create
	p_id = glCreateProgram();
	// attatch
	glAttachShader(p_id, v);
	glAttachShader(p_id, f);
	// link
	glLinkProgram(p_id);
	int success;
	char infoLog[512];
	glGetProgramiv(p_id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(p_id, 512, NULL, infoLog);
		std::cout << "FAILED SHADER LINKING\n" << infoLog << std::endl;
	}
	//delete
	glDeleteShader(v);
	glDeleteShader(f);

}