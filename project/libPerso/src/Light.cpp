#include <libPerso/Light.hpp>

using namespace glm;

int EllipsoidLight::numLights = 0;
int DirectionalLight::numLights = 0;
unsigned int EllipsoidLight::bindingIndex = 1;
unsigned int DirectionalLight::bindingIndex = 2;
std::string EllipsoidLight::uniformName = "uEllipsoidLigths";
std::string DirectionalLight::uniformName = "uDirectionalLights";

// Constructeurs
EllipsoidLight::EllipsoidLight(const vec4 &pos, const vec4 &halfA, const vec4 &lightI)
: position(pos), halfAxes(halfA), lightIntensity(lightI)
{
	numLights++;
}

EllipsoidLight::EllipsoidLight(const aiVector3D v):EllipsoidLight(vec4(v.x, v.y, v.z, 1)){}

EllipsoidLight::EllipsoidLight(const Mesh &mesh){
	position = vec4(mesh.getPosCenter(), 1);
	halfAxes = vec4(mesh.getDimenssion() * 0.5f , 0);
	lightIntensity = vec4(1,1,1,0);
	
	if(mesh.getHasMaterial()) lightIntensity = vec4(mesh.getMaterial().diffuseColor, 0);
	
	numLights++;
}

EllipsoidLight::EllipsoidLight(const EllipsoidLight &l)
: position(l.position), halfAxes(l.halfAxes), lightIntensity(l.lightIntensity)
{
	numLights++;
}
// ---------------------

// Destructeur
EllipsoidLight::~EllipsoidLight(){
	numLights--;
}
// ---------------------

std::ostream & operator<< (std::ostream & os, const EllipsoidLight &light){
	os << "Position : [" << light.position.x << ", " << light.position.y << ", " << light.position.z << "]\n";
	os << "HalfAxes : [" << light.halfAxes.x << ", " << light.halfAxes.y << ", " << light.halfAxes.z << "]\n\n";
	os << "LightIntensity : [" << light.lightIntensity.x << ", " << light.lightIntensity.y << ", " << light.lightIntensity.z << "]\n\n";
	return os;
}

DirectionalLight::DirectionalLight(const vec4 &dir, const vec4 &lightI)
: direction(dir), lightIntensity(lightI)
{
	numLights++;
}

DirectionalLight::DirectionalLight(const aiMesh *mesh)
:DirectionalLight(vec4(
	mesh->mVertices[0].x + mesh->mVertices[1].x,
	mesh->mVertices[0].y + mesh->mVertices[1].y,
	mesh->mVertices[0].z + mesh->mVertices[1].z,
	0
	))
{}


DirectionalLight::DirectionalLight(const DirectionalLight &l)
: direction(l.direction), lightIntensity(l.lightIntensity)
{
	numLights++;
}
// ---------------------

// Destructeur
DirectionalLight::~DirectionalLight(){
	numLights--;
}
// ---------------------

std::ostream & operator<< (std::ostream & os, const DirectionalLight &light){
	os << "Position : [" << light.direction.x << ", " << light.direction.y << ", " << light.direction.z << "]\n";
	os << "LightIntensity : [" << light.lightIntensity.x << ", " << light.lightIntensity.y << ", " << light.lightIntensity.z << "]\n\n";
	return os;
}
