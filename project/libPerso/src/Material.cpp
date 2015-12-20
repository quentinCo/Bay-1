#include <libPerso/Material.hpp>

using namespace glm;

// Constructeurs
Material::Material( glm::vec3 diffColor, glm::vec3 ambColor, glm::vec3 speColor, glm::vec3 emiColor, float shin, float opa )
: diffuseColor(diffColor), ambientColor(ambColor), specularColor(speColor), emissionColor(emiColor), shininess(shin), opacity(opa){};

Material::Material(const aiMaterial *mat){
	if(mat){
		aiColor4D aColor;
		if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &aColor)){
			diffuseColor = vec3(aColor.r, aColor.g, aColor.b);
		}
		if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_AMBIENT, &aColor)){
			ambientColor = vec3(aColor.r, aColor.g, aColor.b);
		}
		if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_SPECULAR, &aColor)){
			specularColor = vec3(aColor.r, aColor.g, aColor.b);
		}
		if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_EMISSIVE, &aColor)){
			emissionColor = vec3(aColor.r, aColor.g, aColor.b);
		}
		if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_SHININESS, &aColor)){
			shininess = aColor.r;
		}
		if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_OPACITY, &aColor)){
			opacity = aColor.r;
		}
	}
	else Material();
};
// ---------------------

// Destructeur
Material::~Material(){};
// ---------------------

std::ostream & operator<< (std::ostream & os, const Material &mat){
	os << "diffuseColor : [" << mat.diffuseColor.x << ", " << mat.diffuseColor.y << ", " << mat.diffuseColor.z << "]\n\n";
	os << "ambientColor : [" << mat.ambientColor.x << ", " << mat.ambientColor.y << ", " << mat.ambientColor.z << "]\n\n";
	os << "specularColor : [" << mat.specularColor.x << ", " << mat.specularColor.y << ", " << mat.specularColor.z << "]\n\n";
	os << "emissionColor : [" << mat.emissionColor.x << ", " << mat.emissionColor.y << ", " << mat.emissionColor.z << "]\n\n";
	os << "shininess : " << mat.shininess << "\n\n";
	os << "opacity : " << mat.opacity << "\n\n";
	return os;
}