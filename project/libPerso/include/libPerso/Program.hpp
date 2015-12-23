#pragma once
#include <iostream>

#include <string>

#include <GL/glew.h>
#include <glimac/Shader.hpp>
#include <glimac/FilePath.hpp>

// glimac Program modifié 
class Program {
private:
	Program& operator =(const Program&);
	
	GLuint m_nGLId;
	static std::string directory;
	
public:
	Program(): m_nGLId(glCreateProgram()) {}

	Program(const Program &p):m_nGLId(p.m_nGLId){}

	~Program() { glDeleteProgram(m_nGLId);}

	Program(Program&& rvalue): m_nGLId(rvalue.m_nGLId) { rvalue.m_nGLId = 0;}

	Program& operator =(Program&& rvalue) {
		m_nGLId = rvalue.m_nGLId;
		rvalue.m_nGLId = 0;
		return *this;
	}
	
	bool operator <(const Program &rvalue)const{
		return m_nGLId < rvalue.m_nGLId;
	}

	GLuint getGLId() const { return m_nGLId; }

	void attachShader(const glimac::Shader& shader) { glAttachShader(m_nGLId, shader.getGLId()); }

	bool link();

	const std::string getInfoLog() const;

	static glimac::FilePath getShadersDirectory();
	static void setShadersDirectory(glimac::FilePath dir);

	void use() const{ glUseProgram(m_nGLId);}
};

// Build a GLSL program from source code
Program buildProgramShader(const GLchar* vsSrc, const GLchar* fsSrc);

// Load source code from files and build a GLSL program
Program loadProgramShader(const glimac::FilePath& vsFile, const glimac::FilePath& fsFile);