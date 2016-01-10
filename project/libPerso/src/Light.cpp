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
	//numLights++;
}

EllipsoidLight::EllipsoidLight(const Mesh &mesh, bool adaptSize){
	position = vec4(mesh.getPosCenter(), 1);
	
	lightIntensity = vec4(3,3,3,0);
	
	if(adaptSize){
		halfAxes = vec4(mesh.getDimension() * 0.5f , 0);
		if(mesh.getHasMaterial())
			lightIntensity = vec4(mesh.getMaterial().emissionColor*1000.f, 0);
	}
	else
		halfAxes = vec4(1, 1, 1, 0);
	
	
	//numLights++;
}

EllipsoidLight::EllipsoidLight(const EllipsoidLight &l)
: position(l.position), halfAxes(l.halfAxes), lightIntensity(l.lightIntensity)
{
	//numLights++;
}
// ---------------------

// Destructeur
EllipsoidLight::~EllipsoidLight(){
	//numLights--;
	std::cout << "DELETE LIGHT ELLIP" << std::endl;
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
	//numLights++;
}

DirectionalLight::DirectionalLight(const aiMesh *mesh, const aiMaterial *mat)
:DirectionalLight()
{

	if(mesh->HasNormals()) direction = vec4(mesh->mNormals[0].x, mesh->mNormals[0].y, mesh->mNormals[0].z, 0);

	aiColor4D aColor;
	if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_EMISSIVE, &aColor)){
		lightIntensity = vec4(vec3(aColor.r, aColor.g, aColor.b) * 1.f, 0 );
	}
}


DirectionalLight::DirectionalLight(const DirectionalLight &l)
: direction(l.direction), lightIntensity(l.lightIntensity)
{
	//numLights++;
}
// ---------------------

// Destructeur
DirectionalLight::~DirectionalLight(){
	//numLights--;
}
// ---------------------

std::ostream & operator<< (std::ostream & os, const DirectionalLight &light){
	os << "Position : [" << light.direction.x << ", " << light.direction.y << ", " << light.direction.z << "]\n";
	os << "LightIntensity : [" << light.lightIntensity.x << ", " << light.lightIntensity.y << ", " << light.lightIntensity.z << "]\n\n";
	return os;
}
