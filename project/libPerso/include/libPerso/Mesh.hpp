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

class Mesh{
	private :
		// Variables
		glm::vec3 positionCenter;
		glm::vec3 dimenssion;
		
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
		
		// Function
		void saveMinMaxPosition(glm::vec3 &posM, glm::vec3 &posm,const glm::vec3 &pos);
		
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
		Mesh(const Mesh &mesh);
		// ---------------------
		
		// Destructeur
		~Mesh();
		// ---------------------
		
		// Get et Set
		glm::vec3 getPosCenter() const;
		
		glm::vec3 getDimenssion() const;
		
		int getNbVertices() const;
		
		std::vector <Vertex> getVertices() const;
		
		std::vector <uint32_t> getIndices() const;
		
		bool getHasMaterial() const;
		
		Material getMaterial() const;
		
		void setTextures(const std::vector<Texture> &tex);
		// ---------------------
		
		// Methode de dessin
		void drawMesh(const Program &prog );
		// ---------------------
		
		friend std::ostream & operator<< (std::ostream & os, const Mesh &mesh);
};

#endif