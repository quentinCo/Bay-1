#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <cstdlib>

#include <glimac/glm.hpp>

struct Vertex{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 coordsTexture;

	Vertex(
		const glm::vec3 &pos = glm::vec3(0,0,0),
		const glm::vec3 &norm = glm::vec3(0,0,1),
		const glm::vec2 &posTex = glm::vec2(0,0)
	);
	
	Vertex(const Vertex &p);
	~Vertex();
	
	friend std::ostream & operator<< (std::ostream & os, const Vertex &point);
};

#endif