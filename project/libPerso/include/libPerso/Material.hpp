#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
#include <cstdlib>

#include <glimac/glm.hpp>

#include <assimp/scene.h>

struct Material{
	glm::vec3 diffuseColor;
	glm::vec3 ambientColor;
	glm::vec3 specularColor;
	glm::vec3 emissionColor;
	
	float shininess;
	float opacity;
	
	Material(
		glm::vec3 diffColor = glm::vec3(1,1,1),
		glm::vec3 ambColor = glm::vec3(0,0,0),
		glm::vec3 speColor = glm::vec3(1,1,1),
		glm::vec3 emiColor = glm::vec3(0,0,0),
		float shin = 0,
		float opa = 1
	);
	
	Material(const aiMaterial *mat);
	
	~Material();
	
	
	friend std::ostream & operator<< (std::ostream & os, const Material &mat);
};
#endif