#include <libPerso/Mesh.hpp>

using namespace glm;


// Constructeurs
Mesh::Mesh(){}

Mesh::Mesh(const aiMesh *mesh, const aiMaterial *mat): nbVertices(mesh->mNumVertices), hasMaterial(false), hasTexture(false){
	
	vec3 posMax;
	vec3 posMin;
	
	bool normal = mesh->HasNormals();

	if(mat){
		hasMaterial = true;
		material = Material(mat);
	}
	
	if(mesh->mTextureCoords[0]){ hasTexture = true; }

	for(int i = 0; i <nbVertices; i++){	
		vec3 pos = vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
			
		if(i == 0){
			posMax = pos;
			posMin = pos;
		}
		else saveMinMaxPosition(posMax, posMin, pos);
			
			
		vec3 norm = vec3(0,0,1);
		if(normal) norm = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		
		vec2 posTex = vec2(0,0);
		if(hasTexture) posTex= vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		
		Vertex newVertex = Vertex(pos, norm, posTex);
		
		vecVertices.push_back(newVertex);
	}	
	
	for(unsigned int i = 0; i<mesh->mNumFaces; i++){
		for(unsigned int j = 0; j<mesh->mFaces[i].mNumIndices; j++){
			vecIndice.push_back(mesh->mFaces[i].mIndices[j]);
		}
	}
	
	positionCenter = (posMax + posMin) * 0.5f;
	dimension = vec3(abs(posMax.x - posMin.x), abs(posMax.y - posMin.y), abs(posMax.z - posMin.z));

	initBuffer(vecVertices, vecIndice);
}

/*
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
*/

Mesh::Mesh(const Mesh &mesh)
:positionCenter(mesh.positionCenter), dimension(mesh.dimension), nbVertices(mesh.nbVertices),
vbo(mesh.vbo), vecVertices(mesh.vecVertices), ibo(mesh.ibo), vecIndice(mesh.vecIndice), vao(mesh.vao),
material(mesh.material), hasMaterial(mesh.hasMaterial), textures(mesh.textures), hasTexture(mesh.hasTexture)
{}
// ---------------------
	
// Destructeur
Mesh::~Mesh(){}
// ---------------------

// Get
glm::vec3 Mesh::getPosCenter() const{ return positionCenter; }

glm::vec3 Mesh::getDimension() const{ return dimension; }

int Mesh::getNbVertices() const{ return nbVertices; }

std::vector <Vertex> Mesh::getVertices() const{ return vecVertices; }

bool Mesh::getHasMaterial() const { return hasMaterial; }

Material Mesh::getMaterial() const { return material; }

std::vector <uint32_t> Mesh::getIndices() const{ return vecIndice; }

// ---------------------

// Set
void Mesh::setTextures(const std::vector<Texture> &tex){
	textures = tex;
}

// ---------------------

// Sauvegarde des x, y et z min pour le calcul des dimensions et centre du mesh.
void Mesh::saveMinMaxPosition(vec3 &posM, vec3 &posm,const vec3 &pos){
	if(posM.x < pos.x) posM.x = pos.x;
	else if(posm.x > pos.x) posm.x = pos.x;
	
	if(posM.y < pos.y) posM.y = pos.y;
	else if(posm.y > pos.y) posm.y = pos.y;
	
	if(posM.z < pos.z) posM.z = pos.z;
	else if(posm.z > pos.z) posm.z = pos.z;
}
// ---------------------

// Initialisation des buffers
void Mesh::initBuffer(std::vector <Vertex> &vecVertices, std::vector <uint32_t> &vecIndices){
	vbo = Buffers <Vertex> (GL_ARRAY_BUFFER, vecVertices);
	ibo = Buffers <uint32_t> (GL_ELEMENT_ARRAY_BUFFER, vecIndices);
	vao = VAO(vbo, ibo);
}
// ---------------------

// Dessin
void Mesh::drawMesh(const Program &prog ){
	vao.bind();
	ibo.bind();
	
	if(hasMaterial) uniformMaterial(prog);
	if(hasTexture) bindTextures(prog);
	
	glDrawElements(GL_TRIANGLES, ibo.getDataSize(), GL_UNSIGNED_INT, (void*)0);
	
	if(hasTexture) unbindTextures();
	
	ibo.unbind();
	vao.unbind();
}
// ---------------------

// Uniform value 
void Mesh::uniformMaterial(const Program &prog){
	glUniform3fv(glGetUniformLocation(prog.getGLId(), "uMaterial.diffuseColor"),1, value_ptr(material.diffuseColor));
	glUniform3fv(glGetUniformLocation(prog.getGLId(), "uMaterial.ambientColor"),1, value_ptr(material.ambientColor));
	glUniform3fv(glGetUniformLocation(prog.getGLId(), "uMaterial.specularColor"),1, value_ptr(material.specularColor));
	glUniform3fv(glGetUniformLocation(prog.getGLId(), "uMaterial.emissionColor"),1, value_ptr(material.emissionColor));
	glUniform1f(glGetUniformLocation(prog.getGLId(), "uMaterial.shininess"), material.shininess);
	glUniform1f(glGetUniformLocation(prog.getGLId(), "uMaterial.opacity"), material.opacity);
}
// ---------------------

// Bind - unbind textures
void Mesh::bindTextures( const Program &prog ){
	GLuint diffuseNr = 1;
	GLuint normalNr = 1;
	GLuint specularNr = 1;
	GLuint ambiantNr = 1;
	GLuint emissiveNr = 1;
	GLuint shininessNr = 1;
	GLuint opacityNr = 1;
	
	for(GLuint i = 0; i < textures.size(); i++){
		glActiveTexture(GL_TEXTURE0 + i);
	
		std::stringstream ss;
		std::string number;
		std::string name = textures[i].getTypeTexture();
		
		if(name == "Texture_diffuse") ss << diffuseNr++;
		else if(name == "Texture_normal") ss << normalNr++;
		else if(name == "Texture_specular") ss << specularNr++;
		else if(name == "Texture_ambiant") ss << ambiantNr++; 
		else if(name == "Texture_emissive") ss << emissiveNr++;
		else if(name == "Texture_shininess") ss << shininessNr++; 
		else if(name == "Texture_opacity") ss << opacityNr++; 
		
		number = ss.str(); 
		
		// init variable uniform correspondant à la texture
		glUniform1i(glGetUniformLocation(prog.getGLId(), ("u" + name + number).c_str()), i);
		
		
		textures[i].bind(GL_TEXTURE0 + i);
	}
}

void Mesh::unbindTextures(){
	for(GLuint i = 0; i < textures.size(); i++) textures[i].unbind(GL_TEXTURE0 + i);
}
// ---------------------

std::ostream & operator<< (std::ostream & os, const Mesh &mesh){

	os << "Affichage des informations du Mesh : " << std::endl;
	os << "Position Center : " << mesh.getPosCenter() << "\n";
	os << "Dimension : " << mesh.getDimension() << "\n";
	os << "vecVertices :\n";
	for(auto it : mesh.getVertices()) os << it;
	os << "------\n";
	os << "vecIndice :\n";
	for(auto it : mesh.getIndices()) os << it <<"\n";
	os << "------\n";
	return os;
}










