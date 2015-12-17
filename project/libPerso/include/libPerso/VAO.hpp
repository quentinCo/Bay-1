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
		Buffers<uint32_t> *ibo;
	
	public :
		VAO();
		VAO(Buffers<Vertex> &vbo, Buffers<uint32_t> &ibo);
	
		~VAO();
	
		void bind() const;
		void unbind() const;
};

#endif