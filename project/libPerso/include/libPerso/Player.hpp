#ifndef PLAYER_H
#define PLAYER_H

#include <SDL/SDL.h>
#include <cmath>

#include <libPerso/Camera.hpp>
#include <libPerso/PhysicsObject.hpp>

class Player{
	private :
		Camera camera;
		
		glm::vec3 position;
		
		float height;
		float speedDep;
		float speedRotate;
		
		glm::vec3 frontPlayer;
		glm::vec3 leftPlayer;
		
		PhysicsObject collision;	// physique de la camera (collision)
		
		bool mousePositionInit;
		
	public :
		Player(
			const glm::vec3 &pos = glm::vec3(0,0,0),
			const glm::vec3 &frontVector = glm::vec3(0,0,-1),
			float h = 1,
			float speedMove = 0.01,
			float speedAngle = 0.1
		);
		
		~Player();
		//------------------------------TEMPORAIRE
		PhysicsObject &getCollision();
		//----------------------------------------
		void playerRotate(const SDL_MouseMotionEvent &e);
		void playerMove(const Uint8 *keystate);
		
		glm::vec3 moveLeft(float t);
		glm::vec3 moveFront(float t);

		glm::mat4 getViewMatrixPlayer() const;

};

#endif