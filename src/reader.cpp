#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "generator.h"

reader::reader(const char* file_path) {
	str = "";
	read_file(file_path);
}
void reader::read_file(const char* file_path) {
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		file.open(file_path);
		std::stringstream stream;
		stream << file.rdbuf();
		file.close();
		str = stream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << file_path << " FILE NOT READ" << std::endl;
	}
}