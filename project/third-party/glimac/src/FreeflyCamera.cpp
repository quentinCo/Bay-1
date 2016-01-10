#include "glimac/FreeflyCamera.hpp"


FreeflyCamera :: FreeflyCamera() : m_Position(0,0,0), m_fPhi(M_PI), m_fTheta(0){
	this->computeDirectionVectors();
}

void FreeflyCamera :: computeDirectionVectors(){
	m_FrontVector = glm::vec3(std::cos(m_fTheta)*std::sin(m_fPhi), std::sin(m_fTheta), std::cos(m_fTheta)*std::cos(m_fPhi));
	m_LeftVector = glm::vec3(std::sin(m_fPhi + M_PI/2), 0, std::cos(m_fPhi + M_PI/2));		
	m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
}

void FreeflyCamera :: moveLeft(float t){
	m_Position += t * m_LeftVector;
}

void FreeflyCamera :: moveFront(float t){
	m_Position += t * m_FrontVector;
}

void FreeflyCamera :: rotateLeft(float degrees){
	m_fPhi += degrees*M_PI/180;
	this->computeDirectionVectors();
}

void FreeflyCamera :: rotateUp(float degrees){
	m_fTheta += degrees*M_PI/180;
	this->computeDirectionVectors();
}

glm::mat4 FreeflyCamera :: getViewMatrix() const{
	return glm::lookAt(m_Position, m_Position + m_FrontVector,m_UpVector);
}