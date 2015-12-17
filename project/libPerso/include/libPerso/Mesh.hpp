#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <string>

#include <GL/glew.h>

#include <glimac/glm.hpp>
#include <glimac/Program.hpp>

#include <assimp/scene.h>

#include <libPerso/Vertex.hpp>
#include <libPerso/Buffers.hpp>
#include <libPerso/VAO.hpp>

class Mesh{
	private :
		// Variables
		int nbVertices;
		
		Buffers <Vertex> vbo;
		
		Buffers <uint32_t> ibo;
		
		VAO vao;
		
		// Function
		void initBuffer(std::vector <Vertex> &vecVertices, std::vector <uint32_t> &vecIndices);
		
		
	public :
		Mesh();
		Mesh(const aiMesh *mesh, const aiMaterial *mat = NULL);
		Mesh(const Vertex *pointTab,const int sizePointTab, const uint32_t *pointOrderTab, const int sizeOrder);
		Mesh(const std::vector<Vertex> &pointVec, const std::vector <uint32_t> &pointOrderVec);
		
		~Mesh();
		
		int getNbVertices() const;
		
		std::vector <Vertex> getVertices() const;
		
		std::vector <uint32_t> getIndices() const;
		
		
		void drawMesh();
		
		friend std::ostream & operator<< (std::ostream & os, const Mesh &mesh);
};

#endif