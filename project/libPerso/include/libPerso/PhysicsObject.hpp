#ifndef PHYSICS_OBJECT
#define PHYSICS_OBJECT

#include <iostream>
#include <cstdlib>
#include <vector>

#include <glimac/glm.hpp>

#include <btBulletDynamicsCommon.h>

#include <libPerso/Vertex.hpp>
/*

	Class qui défini les box de collision et les différentes propriétés phisque de l'objet (masse, inertie, ...).

*/
class PhysicsObject{

	private :
		btCollisionShape *shape;
		btDefaultMotionState *motionState;
		btRigidBody *body;
		btTransform tranform;
		btVector3 inertia;
		btScalar mass;
		
	public :
		PhysicsObject(const glm::vec3 &dim = glm::vec3(1,1,1), float m = 0.f, const glm::vec3 &pos = glm::vec3(0,0,0), const glm::vec3 &inert = glm::vec3(0,0,0));
		PhysicsObject(std::vector<Vertex> &vertices, float m = 0.f, const glm::vec3 &pos = glm::vec3(0,0,0), const glm::vec3 &inert = glm::vec3(0,0,0));
		
		~PhysicsObject();
		
		glm::mat4 getPhysicsTransformation() const;
		float getMass();
		glm::vec3 getInertia();		
		btRigidBody* getBody();
};

#endif