#ifndef PLAYER_H
#define PLAYER_H

#include <SDL/SDL.h>
#include <cmath>

#include <libPerso/Camera.hpp>

class Player: public Camera{
	private :
		// Ajouter hitbox
		float speedDep;
		float speedRotate;
		
		bool mousePositionInit;
		
	public :
		Player(
			const glm::vec3 &pos = glm::vec3(0,0,0),
			const glm::vec3 &frontVector = glm::vec3(0,0,-1),
			float speedMove = 0.01,
			float speedAngle = 0.1
		);
		
		~Player();
		
		void playerRotate(const SDL_MouseMotionEvent &e);
		void playerMove(const Uint8 *keystate);


};

#endif