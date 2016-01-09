#include <libPerso/Game.hpp>



using namespace glimac;

int main(int argc, char** argv) {
	
	GLuint windowWidth = 800, windowHeight = 800;

	Game *game = Game::getInstanceGame(argv[0], "Bay-1", windowWidth, windowHeight);
	
	game->gamePlay();
	
	return EXIT_SUCCESS;
}
