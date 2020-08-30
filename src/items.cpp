#include "items.h"
#include "utils.h"

std::vector<iteminfomanager> items;

std::string xor_key = "PBG892FXX982ABC*";

iteminfomanager::iteminfomanager(uint16_t id) {
	if (size_t(id) < items.size() && id > -1)
		*this = items[id];
}

std::string iteminfomanager::item_type_to_string() {
	switch (type) {
	case ITEM_TYPE_FIST: return "Fist";
	case ITEM_TYPE_WRENCH: return "Wrench";
	case ITEM_TYPE_FOREGROUND_NO_ANIM: return "Foreground_Block";
	case ITEM_TYPE_BACKGROUND: return "Background_Block";
	case ITEM_TYPE_SEED: return "Seed";
	case ITEM_TYPE_CLOTH: return "Clothing";
	default: return "Unknown";
	}
}

std::string iteminfomanager::cloth_type_to_string() {
	if (type != ITEM_TYPE_ARTIFACT && type != ITEM_TYPE_CLOTH)
		return "None";

	if (type == ITEM_TYPE_ARTIFACT)
		return "Ances";

	switch (cloth_type) {
	case CLOTH_TYPE_HAIR: return "Hair";
	case CLOTH_TYPE_SHIRT: return "Shirt";
	case CLOTH_TYPE_PANTS: return "Pants";
	case CLOTH_TYPE_SHOES: return "Feet";
	case CLOTH_TYPE_FACE: return "Face";
	case CLOTH_TYPE_HAND: return "Hand";
	case CLOTH_TYPE_BACK: return "Back";
	case CLOTH_TYPE_HAT: return "Hat";
	case CLOTH_TYPE_NECK: return "Chest";
	}

	return "Unknown";
}

bool iteminfomanager::setup() {
	uint8_t* data = utils::get_data_from_file("items.dat");
	if (!data)
		return false;

	uint16_t version = *(uint16_t*)(data);
	data += sizeof(version);

	uint32_t total_items_count = *(uint32_t*)(data);
	data += sizeof(total_items_count);

	printf("Total items count: %d\n", total_items_count - 1);
	printf("Items version: %d\n", version);

	for (uint32_t i = 0; i < total_items_count; i++) {
		iteminfomanager item{};

		item.id = uint16_t(i);

		data += 6; //skip

		item.type = *data++;

		data++; //skip

		uint16_t name_len = *(uint16_t*)(data);
		data += sizeof(name_len);

		{
			for (uint16_t j = 0; j < name_len; j++)
				item.name += *data++ ^ (xor_key[(j + i) % xor_key.length()]);
		}

		uint16_t texture_len = *(uint16_t*)(data);
		data += sizeof(texture_len) + texture_len + 14; //skip

		item.break_hits = *data++ / 6;

		data += 4; //skip

		item.cloth_type = *data++;

		item.rarity = *(uint16_t*)(data);
		data += sizeof(item.rarity);

		data++; //skip

		uint16_t extra_file_len = *(uint16_t*)(data);
		data += sizeof(extra_file_len) + extra_file_len + 8; //skip

		{
			for (uint8_t j = 0; j < 4; j++) {
				uint16_t unk = *(uint16_t*)(data);
				data += sizeof(unk) + unk; //skip
			}
		}

		data += 24; //skip

		{
			for (uint8_t j = 0; j < 3; j++) {
				uint16_t unk2 = *(uint16_t*)(data);
				data += sizeof(unk2) + unk2; //skip
			}
		}

		data += 80; //skip

		uint16_t unk3 = *(uint16_t*)(data);
		data += sizeof(unk3) + unk3; //skip

		items.push_back(item);
	}

	return true;
}

void iteminfomanager::build() {
	std::ofstream file("CoreData.txt");

	for (auto item : items)
		file << std::to_string(item.id) + "|" + item.name + "|" + std::to_string(item.rarity) + "|itemflags|" + item.item_type_to_string() +
		"|0|0|" + std::to_string(item.break_hits) + "|0|" + item.cloth_type_to_string() + "\n";

	file.close();
}