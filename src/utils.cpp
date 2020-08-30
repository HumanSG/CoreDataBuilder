#include "utils.h"

uint8_t* utils::get_data_from_file(std::string F_name) {
	std::ifstream file(F_name, std::ifstream::binary | std::ifstream::ate);
	if (!file.is_open())
		return nullptr;

	auto size = file.tellg();
	auto data = new uint8_t[size];

	file.seekg(0, std::ifstream::beg);
	file.read((char*)(data), size);
	file.close();

	return data;
}
