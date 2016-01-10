#include <libPerso/Game.hpp>



using namespace glimac;

int main(int argc, char** argv) {

	Game *game = Game::getInstanceGame(argv[0], "Bay-1", 1920, 1080);
	
	game->gamePlay();
	
	return EXIT_SUCCESS;
}
