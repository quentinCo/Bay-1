#include "glimac/TrackBallCamera.hpp"

TrackBallCamera::TrackBallCamera(float dist, float angleX, float angleY) : m_fDistance(dist), m_fAngleX(angleX), m_fAngleY(angleY) {}	

void TrackBallCamera::moveFront(float delta){
	m_fDistance -= delta;
}

void TrackBallCamera::rotateLeft(float degrees){
	m_fAngleX += degrees;
}

void TrackBallCamera::rotateUp(float degrees){
	m_fAngleY += degrees;
}

glm::mat4 TrackBallCamera::getViewMatrix() const{
	glm::mat4 ViewMatrix = glm::mat4();
	ViewMatrix = glm::rotate(ViewMatrix, (float)(m_fAngleX*M_PI) / 180, glm::vec3(1,0,0)); 
	ViewMatrix = glm::rotate(ViewMatrix, (float)(m_fAngleY*M_PI) / 180, glm::vec3(0,1,0)); 
	ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0, 0, m_fDistance));
	return ViewMatrix;
}
