#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>

#include <glimac/Image.hpp>

#include <GL/glew.h>

class Texture{

	private :
		GLuint textureId;
		std::string textureType;		
		std::string texturePath;
		
	public :
	
		
		Texture();
		Texture(std::string meshPath, std::string texPath, std::string type);
		~Texture();
		
		GLuint getIdTexture() const;
		std::string getTypeTexture() const;
		std::string getPathTexture() const;
		
		int initTexture(std::string meshPath, std::string texPath, std::string type);
		void bind(GLenum texture);
		void unbind(GLenum texture);
		
		friend std::ostream & operator<< (std::ostream & os, const Texture &tex);
};

#endif