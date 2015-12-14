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
		std::vector <T> data;
	
	public :
		Buffers(){}
	
		Buffers(const GLenum t,const std::vector<T> &d):target(t), data(d){
			glGenBuffers(1,&buffer);
			glBindBuffer(target, buffer);
			glBufferData(target, data.size()*sizeof(T), data.data(), GL_STATIC_DRAW);
			glBindBuffer(target, 0);
		}
		
		Buffers(const Buffers<T> &b):target(b.target), data(b.data){
			glGenBuffers(1,&buffer);
			glBindBuffer(target, buffer);
			glBufferData(target, data.size()*sizeof(T), data.data(), GL_STATIC_DRAW);
			glBindBuffer(target, 0);
		}
		
		~Buffers(){}
	
		GLuint getBuffer()const{
			return buffer;
		}
		GLenum getTarget()const{
			return target;
		}
		int getDataSize()const{
			return data.size();
		}
		std::vector<T> getData()const{
			return data;
		}
		
		void bind() const{
			glBindBuffer(target, buffer);
		}
		
		void unbind() const{
			glBindBuffer(target, 0);
		}
};

#endif