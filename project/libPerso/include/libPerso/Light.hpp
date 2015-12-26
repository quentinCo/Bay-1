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
	static int numLights;
	
	glm::vec4 position;
	glm::vec4 halfAxes;
	glm::vec4 lightIntensity;

	EllipsoidLight(
		const glm::vec4 &pos = glm::vec4(1,1,1,1),
		const glm::vec4 &halfA = glm::vec4(1,1,1,0),
		const glm::vec4 &lightI= glm::vec4(1,1,1,0)
	);
	
	EllipsoidLight(const EllipsoidLight &p);
	~EllipsoidLight();
	
	friend std::ostream & operator<< (std::ostream & os, const EllipsoidLight &point);
};

void bindLights(const Program &prog, const EllipsoidLight *lights);
void setLights();

#endif
