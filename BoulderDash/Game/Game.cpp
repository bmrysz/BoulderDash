#include "Game.h"

Game::Game() {

}

Game::~Game() {

}

void Game::initialize(const std::string& title) {
	// tworzy logger
	log = Logger("logger.txt");

	log << "application: " + title;
	log << "start: " + log.getCurrentDateAndTime();

	Setup setup = configure.load();

	try {
		// tworzy okno programu
		initWindow(setup.width, setup.height, title);

		// tworzy grafikê
		graphics.initialize(setup.width, setup.height, setup.fullscreen);
		
		// tworzy interfejs DirectInput
		di.init(getWindowHandle());

		// load level
		loadLevels();
	} catch (std::runtime_error e) {
		log << e.what();
	}
}

void Game::handleInput() {
	
}

void Game::handleMessage(MSG msg) {
	
}

void Game::render() {
	unsigned int lvlIndex = 0;

	graphics.render(levels.at(lvlIndex));
}

void Game::updateVariables(float dt) {

}

void Game::loadLevels() {
	Level level = readLevel("Levels/level.lvl");

	levels.push_back(level);
}

Level Game::readLevel(const std::string& levelPath) {
	Level level;

	std::ifstream file(levelPath);

	std::string line;

	unsigned int row = 0;

	std::vector<BLOCK_TYPE> blockLine;

	BLOCK_TYPE block = BLOCK_TYPE::UNDEFINED;

	while (std::getline(file, line)) {
		for (unsigned int col = 0; col < line.size(); ++col) {
			switch (line[col]) {

			case 'H':
				block = BLOCK_TYPE::HERO;
				level.HEROpositionX = col;
				level.HEROpositionY = row;
				break;

			case 'X':
				block = BLOCK_TYPE::EXIT;
				level.EXITpositionX = col;
				level.EXITpositionY = row;
				break;

			case ' ':
				block = BLOCK_TYPE::EMPTY;
				level.numberEMPTYs++;
				break;

			case '.':
				block = BLOCK_TYPE::DIRT;
				level.numberDIRTs++;
				break;

			case '#':
				block = BLOCK_TYPE::WALL;
				level.numberWALLs++;
				break;

			case '@':
				block = BLOCK_TYPE::STONE;
				level.numberSTONEs++;
				break;

			default:
				block = BLOCK_TYPE::UNDEFINED;
				break;
			}

			blockLine.push_back(block);
		}

		level.blocks.push_back(blockLine);
		blockLine.clear();

		++row;
	}

	return level;
}