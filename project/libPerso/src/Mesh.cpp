#include "libPerso/Mesh.hpp"

using namespace glm;


// Constructeurs
Mesh::Mesh(){}

Mesh::Mesh(const aiMesh *mesh, const aiMaterial *mat): nbVertices(mesh->mNumVertices){
	bool normal = mesh->HasNormals();

	for(int i = 0; i <nbVertices; i++){
		vec3 pos = vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

		vec3 col = vec3(1,1,1);
		vec3 amb = vec3(0,0,0);
		vec3 spec = vec3(0,0,0);
		vec3 emi = vec3(0,0,0);
		
		
		if(mat){
			aiColor4D aColor;
			if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &aColor)){
				col = vec3(aColor.r, aColor.g, aColor.b);
			}
			if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_AMBIENT, &aColor)){
				amb = vec3(aColor.r, aColor.g, aColor.b);
			}
			if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_SPECULAR, &aColor)){
				spec = vec3(aColor.r, aColor.g, aColor.b);
			}
			if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_EMISSIVE, &aColor)){
				emi = vec3(aColor.r, aColor.g, aColor.b);
			}
		}
				
		vec3 norm;
		if(normal) norm = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		else norm = vec3(0,0,1);
		
		vecVertices.push_back(Vertex(pos, col, norm, amb, spec, emi));
	}	
	
	for(int i = 0; i<mesh->mNumFaces; i++){
		for(int j = 0; j<mesh->mFaces[i].mNumIndices; j++){
			vecIndice.push_back(mesh->mFaces[i].mIndices[j]);
		}
	}
	initBuffer();
}

Mesh::Mesh(const Vertex *pointTab,const int sizePointTab, const uint32_t *pointOrderTab, const int sizeOrder): nbVertices(sizePointTab){

	for(int i = 0; i<sizePointTab; i++) vecVertices.push_back(pointTab[i]);
	for(int i = 0; i<sizeOrder; i++) vecIndice.push_back(pointOrderTab[i]);
	
	initBuffer();
}

Mesh::Mesh(const std::vector<Vertex> &pointVec, const std::vector <uint32_t> &pointOrderVec): nbVertices(pointVec.size()){
	
	for(int i = 0; i<nbVertices; i++) vecVertices.push_back(pointVec[i]);
	for(int i = 0; i<pointOrderVec.size(); i++) vecIndice.push_back(pointOrderVec[i]);
	
	initBuffer();
}
// ---------------------
	
// Destructeur
Mesh::~Mesh(){}
// ---------------------

// Get
int Mesh::getNbVertices() const{ return nbVertices; }

GLuint Mesh::getVBO() const{ return vbo; }

std::vector <Vertex> Mesh::getVertices() const{ return vecVertices; }

GLuint Mesh::getIBO() const{ return ibo; }

std::vector <uint32_t> Mesh::getIndices() const{ return vecIndice; }

GLuint Mesh::getVAO() const{ return vao; }
// ---------------------

// Initialisation des buffers
void Mesh::initBuffer(){
	initVBO();
	initIBO();
	initVAO();
}

void Mesh::initVBO(){

	glGenBuffers(1,&vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,nbVertices*sizeof(Vertex), vecVertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Mesh::initIBO(){

	glGenBuffers(1,&ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vecIndice.size()*sizeof(uint32_t), vecIndice.data(),GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
}

void Mesh::initVAO(){

	glGenVertexArrays(1, &vao);
	
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);	
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);	
	glEnableVertexAttribArray(5);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, position));
	glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, color));
	glVertexAttribPointer(2,3,GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, normal));
	
	glVertexAttribPointer(3,3,GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, ambientColor));
	glVertexAttribPointer(4,3,GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, specularColor));
	glVertexAttribPointer(5,3,GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, emissionColor));
	
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
// ---------------------

// Dessin
void Mesh::drawMesh(){
	/*std::cout << "// -- >> drawMesh()" << std::endl;
	if(glIsVertexArray(vao))std::cout<<"VAO BIND"<<std::endl;
	if(glIsBuffer(vbo))std::cout<<"VBO BIND"<<std::endl;*/
	
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	
	glDrawElements(GL_TRIANGLES, vecIndice.size(), GL_UNSIGNED_INT, (void*)0);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
// ---------------------

std::ostream & operator<< (std::ostream & os, const Mesh &mesh){

	os << "Affichage des informations du Mesh : " << std::endl;
	os << "vecVertices :\n";
	for(auto it : mesh.getVertices()) os << it;
	os << "------\n";
	os << "vecIndice :\n";
	for(auto it : mesh.getIndices()) os << it <<"\n";
	os << "------\n";
	return os;
}










