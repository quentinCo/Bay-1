#pragma once
#include <iostream>

#include <string>
#include <map>

#include <GL/glew.h>
#include <glimac/Shader.hpp>
#include <glimac/FilePath.hpp>

// glimac Program modifié 
class Program {
private:
	Program& operator =(const Program&);
	
	GLuint m_nGLId;
	static std::string directory;
	static std::map<GLuint, unsigned int> occurenceCounter;
	
public:
	Program();

	Program(const Program &p);

	~Program();

	Program(Program&& rvalue);

	Program& operator =(Program&& rvalue);
	
	bool operator <(const Program &rvalue)const;

	GLuint getGLId() const ;

	void attachShader(const glimac::Shader& shader);

	bool link();

	const std::string getInfoLog() const;

	static glimac::FilePath getShadersDirectory();
	static void setShadersDirectory(glimac::FilePath dir);

	void use() const;
};

// Build a GLSL program from source code
Program buildProgramShader(const GLchar* vsSrc, const GLchar* fsSrc);

// Load source code from files and build a GLSL program
Program loadProgramShader(const glimac::FilePath& vsFile, const glimac::FilePath& fsFile);