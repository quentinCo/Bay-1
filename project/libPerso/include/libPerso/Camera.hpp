#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include <glimac/glm.hpp>
#include <glimac/SDLWindowManager.hpp>

class Camera{
	private :
		glm::vec3 m_Position;		// Position camera
		float m_fPhi;			// Coordonnée spherique XZ
		float m_fTheta;			// Coordonnée spherique YZ
		glm::vec3 m_FrontVector;	
		glm::vec3 m_LeftVector;		
		glm::vec3 m_UpVector;
	
		// Calcule des vecteurs
		void computeDirectionVectors();
		// ---------------------

	public :
		// Constructeur
		Camera(const glm::vec3 &pos = glm::vec3(0,0,0), const glm::vec3 &frontVector = glm::vec3(0,0,-1));
		// ---------------------

		// Destructeur
		virtual ~Camera();
		// ---------------------

		// Get et set
		glm::vec3 getPosition() const;
		float getPhi() const;
		float getTheta() const;
		glm::vec3 getFrontVector() const;	
		glm::vec3 getLeftVector() const;	
		glm::vec3 getUpVector() const;
		
		void setPosition(glm::vec3 pos);
		void setPhi(float radian);
		void setTheta(float radian);
		// ---------------------
		
		// Calcul de position
		virtual void moveLeft(float t);
		virtual void moveFront(float t);
		virtual void moveTop(float t);
		// ---------------------
		
		// Calcul d'inclinaison
		virtual void rotateLeft(float degrees);
		void rotateUp(float degrees);
		// ---------------------
		
		// View Matrice
		virtual glm::mat4 getViewMatrix(const glm::mat4 &t = glm::mat4(1.0)) const;
		// ---------------------
		
		friend std::ostream & operator<< (std::ostream & os, const Camera &cam);
};

#endif