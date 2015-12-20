#include <iostream>
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
		Camera();
		// ---------------------

		// Destructeur
		~Camera();
		// ---------------------

		// Get
		glm::vec3 getPosition() const;
		float getPhi() const;
		float getTheta() const;
		glm::vec3 getFrontVector() const;	
		glm::vec3 getLeftVector() const;	
		glm::vec3 getUpVector() const;
		// ---------------------
		
		// Calcul de position
		void moveLeft(float t);
		void moveFront(float t);
		void moveTop(float t);
		// ---------------------
		
		// Calcul d'inclinaison
		void rotateLeft(float degrees);
		void rotateUp(float degrees);
		// ---------------------
		
		// View Matrice
		glm::mat4 getViewMatrix() const;
		// ---------------------
		
		friend std::ostream & operator<< (std::ostream & os, const Camera &cam);
};