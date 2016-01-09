#pragma once

#include <vector>
#include <GL/glew.h>
#include <iostream>

#include "glimac/glm.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include "Shader.hpp"


using namespace glimac;

class Skybox{

public:
	Skybox();

	Shader skyboxShader;
	GLuint SkyboxTexture;
	GLuint skyboxVAO, skyboxVBO;
	std::vector<const GLchar*> faces;
	GLuint loadCubemap(std::vector<const GLchar*> faces);

private:
	GLfloat skyboxVertices[108];
	//std::vector<const GLchar*> faces;

	GLuint loadTexture(GLchar* path);
	
};
