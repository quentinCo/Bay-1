#ifndef BUFFERS_H
#define BUFFERS_H

#include <iostream>
#include <cstdlib>
#include <vector>

#include <GL/glew.h>

template<typename T>

class Buffers{
	private :
		GLuint buffer;
		GLenum target;
		int size;
	
	public :
		// Constructeur
		Buffers(){}
	
		Buffers(const GLenum t,const std::vector<T> &d):target(t), size(d.size())/*, data(d)*/{
			glGenBuffers(1,&buffer);
			glBindBuffer(target, buffer);
			glBufferData(target, d.size()*sizeof(T), d.data(), GL_STATIC_DRAW);
			glBindBuffer(target, 0);
		}
		// ---------------------
		
		// Destructeur
		~Buffers(){}
		// ---------------------
		
		// Get 
		GLuint getBuffer()const{
			return buffer;
		}
		GLenum getTarget()const{
			return target;
		}
		int getDataSize()const{
			return size;
		}
		// ---------------------
		
		// Bind et unbind
		void bind() const{
			glBindBuffer(target, buffer);
		}
		
		void unbind() const{
			glBindBuffer(target, 0);
		}
		// ---------------------
};

#endif