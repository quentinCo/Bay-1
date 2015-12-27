#include <libPerso/PhysicsObject.hpp>



// Constructeur -> créé un PhysicsObject de base de forme capsule (utile pour le playeur).
PhysicsObject :: PhysicsObject(const glm::vec3 &dim, float m, const glm::vec3 &pos, const glm::vec3 &inert){
	
	shape = new btCapsuleShape(dim.x/2, dim.y);		// créé la forme de la boite.
	
	tranform.setIdentity(); // à voir
	tranform.setOrigin( btVector3(pos.x,pos.y,pos.z) );	// potion de la boite.
	
	mass = btScalar(m);					// mass de l'objet, si la masse est égale à 0 alors l'objet est fixe.
	inertia = btVector3(inert.x, inert.y, inert.z);
	
	if (mass > 0) shape->calculateLocalInertia(mass, inertia);	// calcul de l'inertie de l'objet.
	
	motionState = new btDefaultMotionState (tranform);		
	
	btRigidBody::btRigidBodyConstructionInfo bodyConstructionInfo (mass, motionState, shape, inertia);	// Liaison de toutes les caractéristiques.
	
	body = new btRigidBody (bodyConstructionInfo);		// Création du corps.
}

// Constructeur -> créé (normalement) un objet de collision pour un mesh en re créant un maillage à partir des points du mesh (oui, c'est con et lourd).
PhysicsObject :: PhysicsObject(std::vector<Vertex> &vertices, float m, const glm::vec3 &pos, const glm::vec3 &inert ){
	
	btConvexHullShape *convexHullShape = new btConvexHullShape();
	
	for(auto it : vertices){
		convexHullShape->addPoint(btVector3(it.position.x, it.position.y, it.position.z));
	}
	
	shape = convexHullShape;
	
	tranform.setIdentity();
	tranform.setOrigin( btVector3(pos.x,pos.y,pos.z) );
	
	mass = btScalar(m);
	inertia = btVector3(inert.x, inert.y, inert.z);
	
	if (mass > 0) shape->calculateLocalInertia(mass, inertia);
	
	motionState = new btDefaultMotionState (tranform);
	
	btRigidBody::btRigidBodyConstructionInfo bodyConstructionInfo (mass, motionState, shape, inertia);
	
	body = new btRigidBody (bodyConstructionInfo);
}

// Si le constructeur est en commentaire c'est pas grave, il y a un bogue avec les destructeurs, ils sont appelés quand il faut pas.
// Por le moment ça doit causer une permete de mémoire.
PhysicsObject :: ~PhysicsObject(){
	/*delete(shape);
	delete(motionState);
	delete(body);*/
}

// Censé récupérer le matrice de transformationdel'objet.
glm::mat4 PhysicsObject :: getPhysicsTransformation() const{
	btScalar matrix[16];
	glm::mat4 transformation = glm::mat4();
	
	motionState->m_graphicsWorldTrans.getOpenGLMatrix(matrix);
	
	int j = -1;
	for(int i = 0; i < 16; i++){
		if(i % 4 == 0) j++;
		transformation[j][i%4] = matrix[i];
	}
	
	return transformation;
}

float PhysicsObject :: getMass(){ return mass; }

glm::vec3 PhysicsObject :: getInertia(){ return glm::vec3(inertia.x(), inertia.y(), inertia.z()); }

btRigidBody* PhysicsObject :: getBody(){ return body; }
