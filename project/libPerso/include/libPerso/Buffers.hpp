#ifndef BUFFERS_H
#define BUFFERS_H

#include <iostream>
#include <cstdlib>
#include <map>

#include <GL/glew.h>

template<typename T>

class Buffers{
	private :
		GLuint buffer;
		GLenum target;
		int size;
		static std::map<GLuint, unsigned int> occurenceCounter;
	
	public :
		// Constructeur
		Buffers(){}
	
		Buffers(const GLenum t,const std::vector<T> &d):target(t), size(d.size()){
			glGenBuffers(1,&buffer);
			glBindBuffer(target, buffer);
			glBufferData(target, d.size()*sizeof(T), d.data(), GL_STATIC_DRAW);
			glBindBuffer(target, 0);
			
			occurenceCounter[buffer]++;
		}
		
		Buffers(const Buffers<T> &b):buffer(b.buffer), target(b.target), size(b.size){
			occurenceCounter[buffer]++;
		}
				
		Buffers& operator =(Buffers<T>&& rvalue) {
			buffer = rvalue.buffer;
			target = rvalue.target;
			size = rvalue.size;
			
			rvalue.buffer = 0; // Plus de buffer
			
			return *this;
		}
		
		// ---------------------
		
		// Destructeur
		~Buffers(){
			occurenceCounter[buffer]--;
	
			if(occurenceCounter[buffer] == 0) glDeleteBuffers(1,&buffer);
		}
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

template<typename T>
std::map<GLuint, unsigned int>  Buffers<T>::occurenceCounter;

#endif