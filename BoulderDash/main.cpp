#include "Game/Game.h"

using namespace utility;
using namespace bmath;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	Game* game = new Game();

	//Game game;

	//game.initialize("BoulderDash");
	//game.fixedMainLoop();

	game->initialize("CaveMaster");
	game->fixedMainLoop();

	delete game;

	return 0;
}