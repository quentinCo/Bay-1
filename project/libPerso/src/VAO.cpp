#include <libPerso/VAO.hpp>

VAO::VAO(){}

VAO::VAO(Buffers<Vertex> &vbo, Buffers<uint32_t> &ibo){
	glGenVertexArrays(1,&vao);
	
	glBindVertexArray(vao);
	ibo.bind();
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);	
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);	
	glEnableVertexAttribArray(5);
	
	vbo.bind();
	
	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, position));
	glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, color));
	glVertexAttribPointer(2,3,GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, normal));
	
	glVertexAttribPointer(3,3,GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, ambientColor));
	glVertexAttribPointer(4,3,GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, specularColor));
	glVertexAttribPointer(5,3,GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, emissionColor));
	
	vbo.unbind();
	ibo.unbind();
	glBindVertexArray(0);
	
}

VAO::~VAO(){};

void VAO::bind() const{
	glBindVertexArray(vao);
}

void VAO::unbind() const{
	glBindVertexArray(0);
}