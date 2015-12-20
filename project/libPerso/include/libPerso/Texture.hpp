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
		
		int initTexture(std::string meshPath, std::string texPath, std::string type);
		
	public :
	
		// Constructeur
		Texture();
		Texture(std::string meshPath, std::string texPath, std::string type);
		// ---------------------
		
		// Destructeur
		~Texture();
		// ---------------------
		
		// Get
		GLuint getIdTexture() const;
		std::string getTypeTexture() const;
		std::string getPathTexture() const;
		// ---------------------
		
		// Bind et unbind des textures
		void bind(GLenum texture);
		void unbind(GLenum texture);
		// ---------------------
		
		friend std::ostream & operator<< (std::ostream & os, const Texture &tex);
};

#endif