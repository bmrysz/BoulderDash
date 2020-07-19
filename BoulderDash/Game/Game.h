#pragma once

#include <vector>
#include "Utility.h"
#include "..\Graphics\Graphics.h"
#include "Level.h"

using namespace utility;

class Game : public Application {
public:
	void initialize(const std::string& title);

	Game();
	~Game();
private:
	// overloaded function
	void handleInput() override;
	void handleMessage(MSG msg) override;
	void render() override;
	void updateVariables(float dt) override;

	void loadLevels();
	Level readLevel(const std::string& levelPath);

	// interfaces
	DirectInput di;

	AssetManager am;
	Logger log;
	Configure configure;

	// classes

	Graphics graphics;

	// Levels

	std::vector<Level> levels;
};