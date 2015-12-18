#include <libPerso/Texture.hpp>

Texture::Texture(){}

Texture::Texture(std::string meshPath, std::string texPath, std::string type){
	initTexture(meshPath, texPath, type);
}

Texture::~Texture(){}

GLuint Texture::getIdTexture() const{ return textureId; }
std::string Texture::getTypeTexture() const{ return textureType; }
std::string Texture::getPathTexture() const{ return texturePath; }

int Texture::initTexture(std::string meshPath, std::string texPath, std::string type){
	textureType = type;
	texturePath = meshPath+"/"+texPath;

	std::unique_ptr <glimac::Image> imageMap = glimac::loadImage(texturePath.c_str());
	
	if(!imageMap){
		std::cerr << "Erreur dans le chargement de la texture "<< texturePath <<std::endl;
		return EXIT_FAILURE;
	}
	else std::cout << "\t" << texturePath <<std::endl;

	glGenTextures(1, &textureId);

	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		GL_RGBA, 
		imageMap->getWidth(), 
		imageMap->getHeight(), 
		0, 
		GL_RGBA, 
		GL_FLOAT,
		imageMap->getPixels()
	);
	
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
	glBindTexture(GL_TEXTURE_2D, 0);
	
	return 0;
}

void Texture::bind(GLenum texture){
	glActiveTexture(texture);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::unbind(GLenum texture){
	glActiveTexture(texture);
	glBindTexture(GL_TEXTURE_2D, 0);
}

std::ostream & operator<< (std::ostream & os, const Texture &tex){
	os << "TEXTURE :" << "\n";
	os << "\ttextureId : " << tex.getIdTexture() << "\n";
	os << "\ttextureType : " << tex.getTypeTexture() << "\n";
	os << "\ttexturePath : " << tex.getPathTexture() <<"\n";
	os << "--------------------------- \n";
	return os;
}
