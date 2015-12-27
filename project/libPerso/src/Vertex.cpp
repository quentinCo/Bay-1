#include <libPerso/Vertex.hpp>

using namespace glm;

// Constructeurs
Vertex::Vertex(const vec3 &pos, const vec3 &norm, const vec2 &posTex)
: position(pos), normal(norm), coordsTexture(posTex)
{}

Vertex::Vertex(const Vertex &p)
: position(p.position), normal(p.normal), coordsTexture(p.coordsTexture)
{}
// ---------------------

// Destructeur
Vertex::~Vertex(){}
// ---------------------

std::ostream & operator<< (std::ostream & os, const Vertex &point){
	os << "Position : [" << point.position.x << ", " << point.position.y << ", " << point.position.z << "]\n";
	os << "Normal : [" << point.normal.x << ", " << point.normal.y << ", " << point.normal.z << "]\n\n";
	os << "PosTexture : [" << point.coordsTexture.x << ", " << point.coordsTexture.y << "]\n\n";
	return os;
}