#include <libPerso/Vertex.hpp>

using namespace glm;

// Constructeurs
Vertex::Vertex(vec3 pos, vec3 col, vec3 norm, vec3 amb, vec3 spec, vec3 emi)
: position(pos), color(col), normal(norm), ambientColor(amb), specularColor(spec), emissionColor(emi)
{}

Vertex::Vertex(const Vertex &p)
: position(p.position), color(p.color), normal(p.normal), ambientColor(p.ambientColor), specularColor(p.specularColor), emissionColor(p.emissionColor)
{}
// ---------------------

// Destructeur
Vertex::~Vertex(){}
// ---------------------

std::ostream & operator<< (std::ostream & os, const Vertex &point){
	os << "Position : [" << point.position.x << ", " << point.position.y << ", " << point.position.z << "]\n";
	os << "Color : [" << point.color.x << ", " << point.color.y << ", " << point.color.z << "]\n\n";
	os << "Normal : [" << point.normal.x << ", " << point.normal.y << ", " << point.normal.z << "]\n\n";
	return os;
}