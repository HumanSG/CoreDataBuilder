#include "items.h"
#include <time.h>

int main() {
	srand(uint32_t(time(0)));

	if (!iteminfomanager::setup()) {
		printf("Couldn't setup items, items.dat missing?\n");
		system("PAUSE");
		return 0;
	}

	iteminfomanager::build();

	printf("Successfully built coredata.txt.\n");

	return 0;
}