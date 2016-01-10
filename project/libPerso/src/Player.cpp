#include <libPerso/Player.hpp>

using namespace glm;

Player :: Player(const vec3 &pos, const vec3 &frontVector, float speedMove, float speedAngle)
: Camera(glm::vec3(pos.x, pos.y, pos.z) , frontVector), speedDep(speedMove), speedRotate(speedAngle), mousePositionInit(false){
	frontPlayer = vec3(std::cos(0)*std::sin(getPhi()), std::sin(0), std::cos(0)*std::cos(getPhi()));
}

Player :: ~Player(){}

void Player :: moveLeft(float t){
	Camera :: moveLeft(t);
}

void Player :: moveFront(float t){
	setPosition(t * frontPlayer + getPosition());
}

void Player :: moveTop(float t){
	Camera :: moveTop(t);
}


void Player :: rotateLeft(float degrees){
	Camera :: rotateLeft(degrees);
	frontPlayer = vec3(std::cos(0)*std::sin(getPhi()), std::sin(0), std::cos(0)*std::cos(getPhi()));
}

void Player :: playerRotate(const SDL_MouseMotionEvent &e){
	// if présent pour évité la détection du placement du curseur au centre de la fenetre
	if(mousePositionInit){
		//std::cout << "mouse : " << e.motion.xrel << " -- "<<e.motion.yrel<<std::endl;
		rotateUp(-e.yrel * speedRotate);
		rotateLeft(-e.xrel * speedRotate);
	}
	else mousePositionInit = true;
}

void Player :: playerMove(const Uint8 *keystate){
	if ( keystate[SDLK_z]) moveFront(speedDep);
	else if ( keystate[SDLK_s]) moveFront(-speedDep);

	if ( keystate[SDLK_q]) moveLeft(speedDep);
	else if ( keystate[SDLK_d]) moveLeft(-speedDep);

	if ( keystate[SDLK_SPACE]) moveTop(speedDep);	// Monter
	else if ( keystate[SDLK_RSHIFT] || keystate[SDLK_LSHIFT]) moveTop(-speedDep);	// Descendre	
}
