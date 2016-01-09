#ifndef PLAYER_H
#define PLAYER_H

#include <SDL/SDL.h>
#include <cmath>

#include <libPerso/Camera.hpp>

class Player: public Camera{
	private :
		
		float speedDep;
		float speedRotate;
		
		glm::vec3 frontPlayer;
		
		bool mousePositionInit;
		
	public :
		Player(
			const glm::vec3 &pos = glm::vec3(0,0,0),
			const glm::vec3 &frontVector = glm::vec3(0,0,-1),
			float speedMove = 0.01,
			float speedAngle = 0.1
		);
		
		~Player();

		void moveLeft(float t);
		void moveFront(float t);
		void moveTop(float t);
		void rotateLeft(float degrees);
		
		void playerRotate(const SDL_MouseMotionEvent &e);
		void playerMove(const Uint8 *keystate);


};

#endif