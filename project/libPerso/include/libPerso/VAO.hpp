#ifndef VAO_H
#define VAO_H

#include <iostream>
#include <cstdlib>
#include <vector>

#include <GL/glew.h>

#include <libPerso/Buffers.hpp>
#include <libPerso/Vertex.hpp>

class VAO{

	private :
		GLuint vao;
		static std::map<GLuint, unsigned int> occurenceCounter;
	
	public :
		// Constructeurs
		VAO();
		VAO(Buffers<Vertex> &vbo, Buffers<uint32_t> &ibo);
		VAO(const VAO &v);
		// ---------------------
		
		VAO& operator =(VAO&& rvalue);
		
		// Destructeur
		~VAO();
		// ---------------------
	
		// Bind et unbind
		void bind() const;
		void unbind() const;
		// ---------------------
};

#endif