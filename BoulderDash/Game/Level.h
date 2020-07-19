#pragma once

#include <vector>

enum class BLOCK_TYPE {
	UNDEFINED, HERO, EXIT, EMPTY, DIRT, WALL, STONE
};

struct Level {
	unsigned int HEROpositionX = 0;
	unsigned int HEROpositionY = 0;

	unsigned int EXITpositionX = 0;
	unsigned int EXITpositionY = 0;

	unsigned int numberEMPTYs = 0;
	unsigned int numberDIRTs = 0;
	unsigned int numberWALLs = 0;
	unsigned int numberSTONEs = 0;

	std::vector<std::vector<BLOCK_TYPE>> blocks;
};