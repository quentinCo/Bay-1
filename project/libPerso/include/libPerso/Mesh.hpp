#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <cstring>

#include <GL/glew.h>

#include <glimac/glm.hpp>

#include <assimp/scene.h>

#include <libPerso/Vertex.hpp>
#include <libPerso/Buffers.hpp>
#include <libPerso/VAO.hpp>
#include <libPerso/Material.hpp>
#include <libPerso/Texture.hpp>
#include <libPerso/Program.hpp>
#include <libPerso/PhysicsObject.hpp>

class Mesh{
	private :
		// Variables
		int nbVertices;
		
		Buffers <Vertex> vbo;
		std::vector <Vertex> vecVertices;	// A sup à la version final
		
		Buffers <uint32_t> ibo;
		std::vector <uint32_t> vecIndice;	// A sup à la version final
		
		VAO vao;
		
		Material material;
		bool hasMaterial;
		
		std::vector <Texture> textures;
		bool hasTexture;
		
		PhysicsObject collision;	// Physique du mesh (collision)
		
		// Function
		void initBuffer(std::vector <Vertex> &vecVertices, std::vector <uint32_t> &vecIndices);
		
		void uniformMaterial(const Program &prog);
		
		void bindTextures(const Program &prog);
		void unbindTextures();
		
	public :
		// Constructeurs
		Mesh();
		Mesh(const aiMesh *mesh, const aiMaterial *mat = NULL);
		/*
		Mesh(const Vertex *pointTab,const int sizePointTab, const uint32_t *pointOrderTab, const int sizeOrder);
		Mesh(const std::vector<Vertex> &pointVec, const std::vector <uint32_t> &pointOrderVec);
		*/
		// ---------------------
		
		// Destructeur
		~Mesh();
		// ---------------------
		
		// Get et Set
		int getNbVertices() const;
		
		std::vector <Vertex> getVertices() const;
		
		std::vector <uint32_t> getIndices() const;
		
		PhysicsObject getPhysicsObject() const;
		
		void setTextures(const std::vector<Texture> &tex);
		// ---------------------
		
		// Methode de dessin
		void drawMesh(const Program &prog );
		// ---------------------
		
		friend std::ostream & operator<< (std::ostream & os, const Mesh &mesh);
};

#endif