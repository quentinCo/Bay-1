#include <iostream>
#include <glimac/SDLWindowManager.hpp>

class TrackBallCamera{
	private :
		float m_fDistance, m_fAngleX, m_fAngleY;	
		
	public :
		TrackBallCamera(float dist = -5.0, float angleX = 0.0, float angleY = 0.0);
		
		void moveFront(float delta);
		void rotateLeft(float degrees);
		void rotateUp(float degrees);
		
		glm::mat4 getViewMatrix() const;
};
