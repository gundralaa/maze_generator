#include <glm/glm/glm.hpp>
#include "generator.h"
#include <iostream>
#include <string>

map::map(const char* path) {
	reader grid_reader = reader(path);
	init_grid(&grid_reader);
}
void map::init_grid(reader* read) {
	std::vector<int> in;
	for (const char &c : read->str) {
		switch (c) {
		case '0':
			in.push_back(0);
			break;
		case '*':
			in.push_back(1);
			break;
		case 'c':
			in.push_back(2);
			break;
		case '\n':
			grid.push_back(in);
			in = std::vector<int>();
		}
	}
}
void map::find_wall_pos() {
	for (int r = 1; r < grid.size(); ++r) {
		for (int c = 1; c < grid[0].size(); ++c) {
			// left or right
			if ((grid[r][c - 1] == 0 && grid[r][c] != 0) ||
				(grid[r][c - 1] != 0 && grid[r][c] == 0)) {
				wall_list.push_back(glm::vec3(1.0f * c, 0.0f, 1.0f * r + 0.5f));
				rotate_list.push_back(1);
			}
			// up
			if ((grid[r - 1][c] == 0 && grid[r][c] != 0) ||
				(grid[r - 1][c] != 0 && grid[r][c] == 0)) {
				wall_list.push_back(glm::vec3(1.0f * c + 0.5f, 0.0f, 1.0f * r));
				rotate_list.push_back(0);
			}
			if (grid[r][c] != 0) {
				floor_list.push_back(glm::vec3(1.0f * c + 0.5f, -0.5f, 1.0f * r + 0.5f));
			}
			if (grid[r][c] == 2) {
				cam_pos = glm::vec3(1.0f * c + 0.5f, 0.0f, 1.0f * r + 0.5f);
			}
		}
	}
}