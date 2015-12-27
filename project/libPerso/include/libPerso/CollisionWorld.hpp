#ifndef COLLISION_WORLD
#define COLLISION_WORLD

#include <iostream>
#include <cstdlib>

#include <btBulletDynamicsCommon.h>

#include <libPerso/Mesh.hpp>
#include <libPerso/PhysicsObject.hpp>
/*

	Là c'est la class dans laquelle on met tous les corps de collisions.

*/
class CollisionWorld{

	private :
		btDiscreteDynamicsWorld *world;					// Le monde
		btBroadphaseInterface *broadphase;				// Interface de detection des collisions AABB
		btCollisionDispatcher *dispatcher;				// Support des collisions Convex/Convex et Convex/Concave
		btDefaultCollisionConfiguration *collisionConfig;		// Configuration des allocations mémoires
		btSequentialImpulseConstraintSolver *seqImpulseConstraint;	// Systeme de résolution
		
		float gravity;
		
	public :
		CollisionWorld(float g = 0.981);
		
		~CollisionWorld();
		
		btDiscreteDynamicsWorld* getWorld();
		float getGravity();
		
		void setGravity(float g);
		
		void addToWorld(const Mesh &mesh);
		void updateSimulation();
};

#endif