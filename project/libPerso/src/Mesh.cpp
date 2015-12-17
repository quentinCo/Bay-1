#include <libPerso/Mesh.hpp>

using namespace glm;


// Constructeurs
Mesh::Mesh(){}

Mesh::Mesh(const aiMesh *mesh, const aiMaterial *mat): nbVertices(mesh->mNumVertices){
	std::vector <Vertex> vecVertices;
	std::vector <uint32_t> vecIndice;
	
	bool normal = mesh->HasNormals();

	for(int i = 0; i <nbVertices; i++){
		vec3 pos = vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

		vec3 col = vec3(1,1,1);
		vec3 amb = vec3(0,0,0);
		vec3 spec = vec3(0,0,0);
		vec3 emi = vec3(0,0,0);
		float shi = 0;
		float opa = 1;
		
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
			if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_SHININESS, &aColor)){
				shi = aColor.r;
			}
			if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_OPACITY, &aColor)){
				opa = aColor.r;
			}
		}
				
		vec3 norm;
		if(normal) norm = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		else norm = vec3(0,0,1);
		
		Vertex newVertex = Vertex(pos, col, norm, amb, spec, emi, shi, opa);
		
		vecVertices.push_back(newVertex);
	}	
	
	for(int i = 0; i<mesh->mNumFaces; i++){
		for(int j = 0; j<mesh->mFaces[i].mNumIndices; j++){
			vecIndice.push_back(mesh->mFaces[i].mIndices[j]);
		}
	}
	
	
	initBuffer(vecVertices, vecIndice);
}

Mesh::Mesh(const Vertex *pointTab,const int sizePointTab, const uint32_t *pointOrderTab, const int sizeOrder): nbVertices(sizePointTab){

	std::vector <Vertex> vecVertices;
	std::vector <uint32_t> vecIndice;

	for(int i = 0; i<sizePointTab; i++) vecVertices.push_back(pointTab[i]);
	for(int i = 0; i<sizeOrder; i++) vecIndice.push_back(pointOrderTab[i]);
	
	initBuffer(vecVertices, vecIndice);
}

Mesh::Mesh(const std::vector<Vertex> &pointVec, const std::vector <uint32_t> &pointOrderVec): nbVertices(pointVec.size()){
	
	std::vector <Vertex> vecVertices;
	std::vector <uint32_t> vecIndice;
	
	for(int i = 0; i<nbVertices; i++) vecVertices.push_back(pointVec[i]);
	for(int i = 0; i<pointOrderVec.size(); i++) vecIndice.push_back(pointOrderVec[i]);
	
	initBuffer(vecVertices, vecIndice);
}
// ---------------------
	
// Destructeur
Mesh::~Mesh(){}
// ---------------------

// Get
int Mesh::getNbVertices() const{ return nbVertices; }

std::vector <Vertex> Mesh::getVertices() const{ return vbo.getData(); }

std::vector <uint32_t> Mesh::getIndices() const{ return ibo.getData(); }
// ---------------------

// Initialisation des buffers
void Mesh::initBuffer(std::vector <Vertex> &vecVertices, std::vector <uint32_t> &vecIndices){
	vbo = Buffers <Vertex> (GL_ARRAY_BUFFER, vecVertices);
	ibo = Buffers <uint32_t> (GL_ELEMENT_ARRAY_BUFFER, vecIndices);
	vao = VAO(vbo, ibo);
}
// ---------------------

// Dessin
void Mesh::drawMesh(){
	/*std::cout << "// -- >> drawMesh()" << std::endl;
	if(glIsVertexArray(vao))std::cout<<"VAO BIND"<<std::endl;
	if(glIsBuffer(vbo))std::cout<<"VBO BIND"<<std::endl;*/
	
	vao.bind();
	ibo.bind();
	
	glDrawElements(GL_TRIANGLES, ibo.getDataSize(), GL_UNSIGNED_INT, (void*)0);
	
	ibo.unbind();
	vao.unbind();
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










