#ifndef GENERATOR_H
#define GENERATOR_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "window.h"
#include "shader.h"
#include "camera.h"

// reads txt file
class reader {
public:
	std::string str;
	// reads arbitrary file to str
	reader(const char* file_path);
private:
	void read_file(const char* file_path); // read file and populate str
};

class map {
public:
	std::vector<glm::vec3> wall_list;
	std::vector<int> rotate_list;
	std::vector<glm::vec3> floor_list;
	glm::vec3 cam_pos;
	map(const char* path);
	void find_wall_pos(); // populate seg list
private:
	std::vector<std::vector<int>> grid;
	void init_grid(reader* read);
};

// defines wall vao
class square {
public:
	uint32_t vao = 0;
	square();
	square(shader* p, window* win); // create wall buffers
	void bind(); // bind vao
	void unbind();
	virtual void set_attr(); // set attr pointers
	virtual void init_buff();
protected:
	glm::mat4 model;
	glm::mat4 proj;
	uint32_t tex_id;
	window* win_ptr;
	shader* prog_ptr;
	void init_trans();
	void bind_tex();
	void load_texture(const char* path);
};

// defines wall vao
class wall: public square {
public:
	wall(shader* p, window* win); // create wall buffers
	void draw_walls(map* m, camera* cam);
	void set_attr() override;
	void init_buff() override;
};

// defines wall vao
class tile : public square {
public:
	tile(shader* p, window* win) : square(p, win) {};
	void draw_floors(map* m, camera* cam);
};


#endif
