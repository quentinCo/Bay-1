#include <libPerso/VAO.hpp>

std::map<GLuint, unsigned int> VAO::occurenceCounter;

// Constructeurs
VAO::VAO(){};

VAO::VAO(Buffers<Vertex> &vbo, Buffers<uint32_t> &ibo){
	glGenVertexArrays(1,&vao);
	
	glBindVertexArray(vao);
	ibo.bind();
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);	
	glEnableVertexAttribArray(2);
	
	vbo.bind();
	
	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, position));
	glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, normal));
	glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, coordsTexture));
	
	vbo.unbind();
	ibo.unbind();
	glBindVertexArray(0);
	
	occurenceCounter[vao]++;
	
}

VAO::VAO(const VAO &v):vao(v.vao){ occurenceCounter[vao]++; }

VAO& VAO::operator =(VAO&& rvalue) {
	vao = rvalue.vao;
	
	rvalue.vao = 0; // Plus de buffer
	return *this;
}
// ---------------------

// Destructeur
VAO::~VAO(){
	occurenceCounter[vao]--;
	if(occurenceCounter[vao] == 0) glDeleteVertexArrays(1,&vao);
}
// ---------------------

// Bind et unbind
void VAO::bind() const{
	glBindVertexArray(vao);
}

void VAO::unbind() const{
	glBindVertexArray(0);
}
// ---------------------