#include <libPerso/Player.hpp>

using namespace glm;
// Peut être entièrement changé

Player :: Player(const vec3 &pos, const vec3 &frontVector, float h, float speedMove, float speedAngle)
: camera(glm::vec3(0, h,0) , frontVector),height(h), speedDep(speedMove), speedRotate(speedAngle), mousePositionInit(false){

	// ----> Le frontPlayer n'est pas influencé par la rontation haut - bas contrairement au frontVector camera. Donc tu peux pas décoler du sol.
	frontPlayer = vec3(std::cos(0)*std::sin(camera.getPhi()), std::sin(0), std::cos(0)*std::cos(camera.getPhi()));
	leftPlayer = vec3(std::sin(camera.getPhi() + M_PI/2), 0, std::cos(camera.getPhi() + M_PI/2));
	
	collision = PhysicsObject(vec3(1,h,0), 2, pos);
}

Player :: ~Player(){}

PhysicsObject &Player :: getCollision(){
	return collision;
}

vec3 Player :: moveLeft(float t){
	return t * leftPlayer;
}

vec3 Player :: moveFront(float t){
	return t * frontPlayer;
}

void Player :: playerRotate(const SDL_MouseMotionEvent &e){
	// if présent pour évité la détection du placement du curseur au centre de la fenetre
	if(mousePositionInit){
		//std::cout << "mouse : " << e.motion.xrel << " -- "<<e.motion.yrel<<std::endl;
		camera.rotateUp(-e.yrel * speedRotate);
		// -------------------> Censé intialiser une vitesse angulaire sur y et donc une rotation sur y, mais non.
		collision.getBody()->setAngularVelocity(btVector3(0,-e.xrel * speedRotate,0));
		//rotateLeft(-e.xrel * speedRotate);
		//degrees*M_PI/180
	}
	else mousePositionInit = true;
}

void Player :: playerMove(const Uint8 *keystate){
	btVector3 velocity = btVector3();
	btVector3 temp;
	vec3 tempGlm;

	if ( keystate[SDLK_z]){
		tempGlm = moveFront(speedDep);
		temp = btVector3(tempGlm.x, tempGlm.y, tempGlm.z);
	} 
	else if ( keystate[SDLK_s]){
		tempGlm = moveFront(-speedDep);
		temp = btVector3(tempGlm.x, tempGlm.y, tempGlm.z);
	}
	else temp = btVector3(0,0,0);
	
	velocity += temp;
	
	if ( keystate[SDLK_q]){
		tempGlm = moveLeft(speedDep);
		temp = btVector3(tempGlm.x, tempGlm.y, tempGlm.z);
	} 
	else if ( keystate[SDLK_d]){
		tempGlm = moveLeft(-speedDep);
		temp = btVector3(tempGlm.x, tempGlm.y, tempGlm.z);
	}
	else temp = btVector3(0,0,0);
	
	velocity += temp;
	std::cout << "Velocity : " << velocity.x() << ", " << velocity.y()  << std::endl;
/*
	if ( keystate[SDLK_a]) moveTop(speedDep);	// Monter
	else if ( keystate[SDLK_e]) moveTop(-speedDep);	// Descendre
*/
	// -------------------> Censé initialiser les vitesses en x et y de l'objet pour le mouvement, mais non
	collision.getBody()->setLinearVelocity(velocity);
}

glm::mat4 Player::getViewMatrixPlayer() const{
	mat4 tranformationCollision = collision.getPhysicsTransformation();			// ---> On récupèrer la matrice de transformation 
	std::cout << "tranformationCollision : " << tranformationCollision << std::endl;	// ---> On l'affiche et elle existe.
	return camera.getViewMatrix(tranformationCollision);					// ---> On la passe à la camera pour avoir la MVMatrix, la tranformation et appliqué à la position et aux vecteur, sans les modifiers, et ça marche.
}	
		
		
		
		
		
		
		