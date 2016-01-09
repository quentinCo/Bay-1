#include <libPerso/Camera.hpp>

using namespace glm;

// Constructeurs
Camera :: Camera() : m_Position(0,0,0), m_fPhi(M_PI), m_fTheta(0){
	computeDirectionVectors();
		
	SDL_WM_GrabInput(SDL_GRAB_ON);
	SDL_ShowCursor(SDL_DISABLE);
}
// ---------------------

// Destructeur
Camera :: ~Camera(){
	//SDL_WM_GrabInput(SDL_GRAB_OFF);
	//SDL_ShowCursor(SDL_ENABLE);
}
//----------------------

// Get et set
vec3 Camera::getPosition() const { return m_Position ;}

float Camera::getPhi() const {return m_fPhi;}

float Camera::getTheta() const {return m_fTheta;}

vec3 Camera::getFrontVector() const { return m_FrontVector;}

vec3 Camera::getLeftVector() const { return m_LeftVector;}	

vec3 Camera::getUpVector() const {return m_UpVector;}


void Camera::setPosition(vec3 pos){ m_Position = pos;}

void Camera::setPhi(float radian){
	m_fPhi = radian;
	computeDirectionVectors();
}

void Camera::setTheta(float radian){
	m_fTheta = radian;
	computeDirectionVectors();
}
// ---------------------

// Calcule des vecteurs
void Camera :: computeDirectionVectors(){
/*
	std::cout << "m_fTheta : "<< m_fTheta<<std::endl;
	if(m_fPhi > M_PI/2) m_fPhi = M_PI/2;
	else if(m_fPhi < -M_PI/2) m_fPhi = -M_PI/2;
	
	if(m_fTheta > M_PI/2) m_fTheta = M_PI/2;
	else if(m_fTheta < -M_PI/2) m_fTheta = -M_PI/2;
*/
	m_FrontVector = vec3(std::cos(m_fTheta)*std::sin(m_fPhi), std::sin(m_fTheta), std::cos(m_fTheta)*std::cos(m_fPhi));
	m_LeftVector = vec3(std::sin(m_fPhi + M_PI/2), 0, std::cos(m_fPhi + M_PI/2));		
	m_UpVector = cross(m_FrontVector, m_LeftVector);
}
// ---------------------

// Calcule des positions
void Camera :: moveLeft(float t){
	m_Position += t * m_LeftVector;
}

void Camera :: moveFront(float t){
	m_Position += t * m_FrontVector;
}

void Camera :: moveTop(float t){
	m_Position.y += t;
}
// ---------------------

// Calcule de l'inclinaison
void Camera :: rotateLeft(float degrees){
	m_fPhi += degrees*M_PI/180;
	computeDirectionVectors();
}

void Camera :: rotateUp(float degrees){
	m_fTheta += degrees*M_PI/180;
	computeDirectionVectors();
}
// ---------------------

// View Matrice
mat4 Camera :: getViewMatrix() const{
	return lookAt(m_Position, m_Position + m_FrontVector,m_UpVector);
}
// ---------------------

std::ostream & operator<< (std::ostream & os, const Camera &cam){
	os << "m_Position : " << cam.getPosition() << "\n";
	os << "m_fPhi : " << cam.getPhi() << "\n";
	os << "m_fTheta : " << cam.getTheta() << "\n";
	os << "m_FrontVector : " << cam.getFrontVector() << "\n";
	os << "m_LeftVector : " << cam.getLeftVector() << "\n";
	os << "m_UpVector : " << cam.getUpVector() << "\n";
	return os; 
}
