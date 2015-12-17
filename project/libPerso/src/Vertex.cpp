#include "libPerso/Vertex.hpp"

using namespace glm;

// Constructeurs
Vertex::Vertex(const vec3 &pos, const vec3 &col, const vec3 &norm, const vec3 &amb, const vec3 &spec, const vec3 &emi, const float &shi,const  float &opa)
: position(pos), color(col), normal(norm), ambientColor(amb), specularColor(spec), emissionColor(emi),
shininess(shi), opacity(opa)
{}

Vertex::Vertex(const Vertex &p)
: position(p.position), color(p.color), normal(p.normal), ambientColor(p.ambientColor), specularColor(p.specularColor), emissionColor(p.emissionColor),
shininess(p.shininess), opacity(p.opacity)
{}
// ---------------------

// Destructeur
Vertex::~Vertex(){}
// ---------------------

std::ostream & operator<< (std::ostream & os, const Vertex &point){
	os << "Position : [" << point.position.x << ", " << point.position.y << ", " << point.position.z << "]\n";
	os << "Color : [" << point.color.x << ", " << point.color.y << ", " << point.color.z << "]\n\n";
	os << "Normal : [" << point.normal.x << ", " << point.normal.y << ", " << point.normal.z << "]\n\n";
	os << "ambientColor : [" << point.ambientColor.x << ", " << point.ambientColor.y << ", " << point.ambientColor.z << "]\n\n";
	os << "specularColor : [" << point.specularColor.x << ", " << point.specularColor.y << ", " << point.specularColor.z << "]\n\n";
	os << "emissionColor : [" << point.emissionColor.x << ", " << point.emissionColor.y << ", " << point.emissionColor.z << "]\n\n";
	os << "shininess : " << point.shininess << "\n\n";
	os << "opacity : " << point.opacity << "\n\n";
	return os;
}