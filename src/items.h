#pragma once
#include "enums.h"
#include <string>
#include <vector>

class iteminfomanager {
public:
	iteminfomanager() {}; //default constructor
	iteminfomanager(uint16_t id); //custom constructor 

	uint16_t id = 0;
	uint8_t type = 0;
	uint8_t cloth_type = 0;
	uint8_t break_hits = 3;
	uint16_t rarity = 1;
	std::string name{};
	
	std::string item_type_to_string();
	std::string cloth_type_to_string();

	static bool setup();
	static void build();
};

extern std::vector<iteminfomanager> items;