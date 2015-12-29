#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>
#include <cstdlib>

#include <sstream>
#include <cstring>

#include <assimp/scene.h>

#include <libPerso/Program.hpp>
#include <glimac/glm.hpp>

struct EllipsoidLight{
	static unsigned int numLights;
	static unsigned int bindingIndex;
	static std::string uniformName;
	
	glm::vec4 position;
	glm::vec4 halfAxes;
	glm::vec4 lightIntensity;

	EllipsoidLight(
		const glm::vec4 &pos = glm::vec4(0,0,0,1),
		const glm::vec4 &halfA = glm::vec4(1,1,1,0),
		const glm::vec4 &lightI= glm::vec4(1,1,1,0)
	);
	
	EllipsoidLight(const EllipsoidLight &p);
	~EllipsoidLight();
	
	friend std::ostream & operator<< (std::ostream & os, const EllipsoidLight &point);
};

struct DirectionalLight{
	static unsigned int numLights;
	static unsigned int bindingIndex;
	static std::string uniformName;
	
	glm::vec4 direction;
	glm::vec4 lightIntensity;

	DirectionalLight(
		const glm::vec4 &dir = glm::vec4(1,1,1,0),
		const glm::vec4 &lightI= glm::vec4(1,1,1,0)
	);
	
	DirectionalLight(const DirectionalLight &p);
	~DirectionalLight();
	
	friend std::ostream & operator<< (std::ostream & os, const DirectionalLight &point);
};

template<typename lightT>
void bindLights(const Program &prog, const lightT *lights);

#include <libPerso/Light_impl.hpp>

#endif
