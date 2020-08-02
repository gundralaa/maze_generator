#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

// creates shader program
class shader {
public:
	shader(const char* v_path, const char* f_path){ read_files(v_path, f_path); }
	uint32_t p_id = 0;
	void use();
	void unbind();
	// uniform setters
private:
	const char* v_code;
	const char* f_code;
	void read_files(const char* v_path, const char* f_path);
	void compile_shader(uint32_t id);
	void init_program();
};
#endif