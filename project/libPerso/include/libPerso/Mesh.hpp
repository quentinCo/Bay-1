#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <cstdlib>
#include <vector>

#include <GL/glew.h>

#include <glimac/glm.hpp>

#include <assimp/scene.h>

#include "Vertex.hpp"

class Mesh{
	private :
		// Variables
		int nbVertices;
		
		std::vector <Vertex> vecVertices;
		GLuint vbo;
		
		std::vector <uint32_t> vecIndice;
		GLuint ibo;
		
		GLuint vao;
		
		// Function
		void initBuffer();
		void initVBO();
		void initIBO();
		void initVAO();
		
	public :
		Mesh();
		Mesh(const aiMesh *mesh, const aiMaterial *mat = NULL);
		Mesh(const Vertex *pointTab,const int sizePointTab, const uint32_t *pointOrderTab, const int sizeOrder);
		Mesh(const std::vector<Vertex> &pointVec, const std::vector <uint32_t> &pointOrderVec);
		
		~Mesh();
		
		int getNbVertices() const;
		GLuint getVBO() const;
		std::vector <Vertex> getVertices() const;
		GLuint getIBO() const;
		std::vector <uint32_t> getIndices() const;
		GLuint getVAO() const;
		
		void drawMesh();
		
		friend std::ostream & operator<< (std::ostream & os, const Mesh &mesh);
};

#endif