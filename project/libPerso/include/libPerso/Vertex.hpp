#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <cstdlib>

#include <glimac/glm.hpp>

struct Vertex{
	glm::vec3 position;
	glm::vec3 color; // diffusion color
	glm::vec3 normal;
	glm::vec3 ambientColor;
	glm::vec3 specularColor;
	glm::vec3 emissionColor;
	
	//glm::vec3 transparency;

	Vertex(
		glm::vec3 pos = glm::vec3(0,0,0),
		glm::vec3 col = glm::vec3(1,1,1),
		glm::vec3 norm = glm::vec3(0,0,1),
		glm::vec3 amb = glm::vec3(0,0,0),
		glm::vec3 spec = glm::vec3(0,0,0),
		glm::vec3 emi = glm::vec3(0,0,0)
	);
	
	Vertex(const Vertex &p);
	~Vertex();
	
	friend std::ostream & operator<< (std::ostream & os, const Vertex &point);
};

#endif