#include <libPerso/Player.hpp>

using namespace glm;

Player :: Player(const vec3 &pos, const vec3 &frontVector, float speedMove, float speedAngle): Camera(), speedDep(speedMove), speedRotate(speedAngle), mousePositionInit(false){
	vec3 normalizeFront = normalize(frontVector);
	float theta = asin(normalizeFront.y);

	setTheta(theta);
	setPhi(acos(normalizeFront.z / cos(theta)));
	
	setPosition(pos);	
}

Player :: ~Player(){}

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

	if ( keystate[SDLK_a]) moveTop(speedDep);	// Monter
	else if ( keystate[SDLK_e]) moveTop(-speedDep);	// Descendre
}