#include <libPerso/CollisionWorld.hpp>

CollisionWorld :: CollisionWorld(float g) : gravity(g){

	collisionConfig = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfig);
	broadphase = new btDbvtBroadphase();
	seqImpulseConstraint = new btSequentialImpulseConstraintSolver();
	world = new btDiscreteDynamicsWorld(dispatcher, broadphase, seqImpulseConstraint, collisionConfig);

	world->setGravity(btVector3(0,gravity,0));
}

CollisionWorld :: ~CollisionWorld(){
	/*delete(world);
	delete(broadphase);
	delete(dispatcher);
	delete(collisionConfig);
	delete(seqImpulseConstraint);*/
}

btDiscreteDynamicsWorld* CollisionWorld :: getWorld(){ return world; }

float CollisionWorld :: getGravity(){ return gravity; }

void CollisionWorld :: setGravity(float g){
	gravity = g;
	world->setGravity(btVector3(0,gravity,0));
}

void CollisionWorld :: addToWorld(const Mesh &mesh){
	world->addRigidBody(mesh.getPhysicsObject().getBody());
}

void CollisionWorld :: updateSimulation(){
	world->stepSimulation(1/60.f);
}