#include <libPerso/Scene.hpp>

using namespace std;

// Construteurs
Scene::Scene(){}

Scene::Scene(string path){
	loadScene(path);
}
// ---------------------

// Destructeur
Scene::~Scene(){}
// ---------------------

// Créer la scéne à partir d'un fichier
int Scene::loadScene(string path){
	Assimp::Importer aImporter;
	const aiScene* aScene = aImporter.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);	

	if(!aScene || aScene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !aScene->mRootNode){
		cerr<< "Couldn't open file: " << path<<" \n" << aImporter.GetErrorString() << endl;
		return EXIT_FAILURE;
	}
	else{
		cout << "File open : " << path << endl;
	}
	
	directory = path.substr(0, path.find_last_of('/'));

	map< array<string, 2>, vector<Mesh>> mapNameShader;

	processNode(aScene->mRootNode, aScene, mapNameShader);
	
	for(auto it : mapNameShader){
	//	cout << "it.first[0] : " << it.first[0] << " --- it.first[1] : " << it.first[1] << endl;
		mapMeshByShaders.insert(pair<Program, vector<Mesh>>(loadProgramShader(glimac::FilePath(it.first[0]),glimac::FilePath(it.first[1])), it.second));
	}
	
	return 1;
}
// ---------------------

// Parcours et initialisation des mesh
void Scene::processNode(const aiNode* aNode, const aiScene* aScene, map<array<string, 2>, vector<Mesh>> &mapNameShader){
	for(GLuint i = 0; i < aNode->mNumMeshes; i++)
	{
		//cout << "\n---------------------------------------" <<endl;
		aiMesh* aMesh = aScene->mMeshes[aNode->mMeshes[i]];
	
		aiMaterial *mat;
	
		if(aScene->HasMaterials()) mat = aScene->mMaterials[aMesh->mMaterialIndex];
		else mat = NULL;


		Mesh mesh (aMesh, mat);
		
		mesh.setTextures(processTexture(aMesh, aScene, mat));
		//--------------------------
		addToMapShadersName(mapNameShader, mat, mesh);
		//---------------------------
		//meshes.push_back(mesh);
		//cout << "-------------------------------------" <<endl;	
	}

	for(GLuint i = 0; i < aNode->mNumChildren; i++) processNode(aNode->mChildren[i], aScene, mapNameShader);
}
// ---------------------

// Initialisation des textures
vector<Texture> Scene::processTexture(const aiMesh* aiMesh, const aiScene* scene, const aiMaterial *mat){

	vector<Texture> textures;
	
	cout << "Load Texture : " <<endl;
	
	if(mat){
		vector<Texture> diffuseMaps = loadMaterialTextures(mat, aiTextureType_DIFFUSE, "Texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		vector<Texture> specularMaps = loadMaterialTextures(mat, aiTextureType_SPECULAR, "Texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	
		vector<Texture> ambiantMaps = loadMaterialTextures(mat, aiTextureType_AMBIENT , "Texture_ambiant");
		textures.insert(textures.end(), ambiantMaps.begin(), ambiantMaps.end());
	
		vector<Texture> emissiveMaps = loadMaterialTextures(mat, aiTextureType_EMISSIVE, "Texture_emissive");
		textures.insert(textures.end(), emissiveMaps.begin(), emissiveMaps.end());
	
		vector<Texture> normalMaps = loadMaterialTextures(mat, aiTextureType_HEIGHT , "Texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	
		vector<Texture> shininessMaps = loadMaterialTextures(mat, aiTextureType_SHININESS , "Texture_shininess");
		textures.insert(textures.end(), shininessMaps.begin(), shininessMaps.end());
	
		vector<Texture> opacityMaps = loadMaterialTextures(mat, aiTextureType_OPACITY , "Texture_opacity");
		textures.insert(textures.end(), opacityMaps.begin(), opacityMaps.end());
	} 
	
	return textures;
}


vector<Texture> Scene::loadMaterialTextures(const aiMaterial* mat, const aiTextureType type, string typeName){
	vector<Texture> texturesType;

	//std::cout << typeName << std::endl;
	for(GLuint i = 0; i < mat->GetTextureCount(type); i++){
		aiString str;
		mat->GetTexture(type, i, &str);
		GLboolean skip = false;

		for(GLuint j = 0; j < textures_loaded.size(); j++){
			if(textures_loaded[j].getPathTexture() == str.data){
				texturesType.push_back(textures_loaded[j]);
				skip = true; 
				break;
			}
		}
		if(!skip){

			Texture newTexture(directory, str.data, typeName);
			
			texturesType.push_back(newTexture);

			this->textures_loaded.push_back(newTexture);
		}
	}
	return texturesType;
}
// ---------------------

// Gestion map shader
	// Recupération des noms des shaders pour chaque mesh
void Scene::addToMapShadersName(map<array<string, 2>,vector<Mesh>> &mapNameShader, const aiMaterial *mat, const Mesh mesh){
	cout << "Find Shaders :" << endl;
	if(mat){
		aiString aNameMat;
		mat->Get(AI_MATKEY_NAME, aNameMat);
		
		string nameMat = aNameMat.data;
		
		string nameVs = recoverNameShader(nameMat, "vsShader", '_');
		string nameFs = recoverNameShader(nameMat, "fsShader", '_');
		
		string pathVs = "shaders/" + nameVs + ".vs.glsl";
		pathVs = Program::getShadersDirectory() + pathVs;
		
		string pathFs = "shaders/" + nameFs + ".fs.glsl";
		pathFs = Program::getShadersDirectory() + pathFs;
		
		array<string, 2> pairShaders = {pathVs, pathFs};
		
		if(mapNameShader.find(pairShaders) != mapNameShader.end()) {
			mapNameShader[pairShaders].push_back(mesh);
			cout << "\tAdd to an exitent list" << endl;
		}
		else{
			verifFileShaders(pairShaders[0], ".vs.glsl");
			verifFileShaders(pairShaders[1], ".fs.glsl");
			mapNameShader[pairShaders].push_back(mesh);
		}
	}
}

	// Recuperation du nom des shaders pour dans le nom du matériaux du mesh
string Scene::recoverNameShader (const string &nameMat, const string &begin, char end){
	//------------------------->cout << "recoverName : " << nameMat <<endl;
	size_t posBegin = nameMat.find(begin);
	string nameShader;
	
	if(posBegin != string::npos){
		string step1 = nameMat.substr(nameMat.find(begin));
		nameShader = step1.substr(begin.length(), step1.find_first_of(end)-begin.length());
	}
	else nameShader = "default";
	//-------------------------->cout << "\t" << nameShader << endl;
	return nameShader;
}

	// Verification de l'existance du shader
void Scene::verifFileShaders (string &pathShader, const string &fileExtention){
	//-------------------------->cout << "verifFileShaders : "<< pathShader <<endl;
	if(FILE *file = fopen(pathShader.c_str(), "r")){
		fclose(file);
		cout << "\t" << pathShader << endl;
	}
	else{
		cout << "ERROR :" <<endl;
		cout << "\t The next shader doesn't exist :" << pathShader << endl;
		cout << "\t It was replace by the default shader." << endl;
		pathShader = "shaders/default" + fileExtention;
		pathShader = Program::getShadersDirectory() + pathShader;
	}
}
// --------------------

// Dessin

void Scene::drawScene(const glm::mat4 &globalMVMatrix){
	//for(auto it : meshes) it.drawMesh(prog);

	for(auto it = mapMeshByShaders.begin(); it != mapMeshByShaders.end(); it++){
		it->first.use();
		
		//cout << "ID program : " << it->first.getGLId() << endl;
		/*int ns;   
		glGetProgramiv(it->first.getGLId(), GL_ATTACHED_SHADERS, &ns);   
	
			GLuint *shaders=new GLuint [ns];   
			glGetAttachedShaders(it->first.getGLId(), ns, NULL, shaders);
			for(int i; i<ns; i++){
				cout << shaders[i] << endl;
			}*/
		
		initUniformValue(it->first, globalMVMatrix);
		for(auto mesh : it->second) mesh.drawMesh(it->first);
		
		//Binding des lumières----------------------------------
		EllipsoidLight lights[3]; // Déclaration du tableau des lumières ellipsoïdales, à la place du 3, tu devras mettre le bon nombre de lumières, on en a 100 au maximum
		
		for(unsigned int i = 0; i < EllipsoidLight::numLights; ++i){
			lights[i] = EllipsoidLight(
				glm::vec4(0, 1, 0, 1), // Position du centre de la lumière, la dernière valeur doit rester à 1 vu que c'est un point
				glm::vec4(1, 1, 1, 0), // Coefficients d'étirement, tu la définiras avec ta hitbox, le x devra être la moitié de la largeur, le y la moitié de la hauteur et le z la moitié de la profondeur et dernière valeur à 0
				glm::vec4(1, 10, 1, 0) // Intensité lumineuse, RGB et dernière valeur à 0 
			);
		}
		
		bindLights(it->first, lights); // Ici on envoie les lumières aux programmes de shader
		
		
		DirectionalLight dirlights[1]; // Déclaration du tableau des lumières directionnelles, à la place du 1, tu devras mettre le bon nombre de lumières, on en a 100 au maximum
		
		for(unsigned int i = 0; i < DirectionalLight::numLights; ++i){
			dirlights[i] = DirectionalLight(
				glm::vec4(1, 1, 1, 0), // Direction de la lumière, la dernière valeur doit rester à 0 vu que c'est un point
				glm::vec4(1, 1, 1, 0) // Intensité lumineuse, RGB et dernière valeur à 0 
			);
		}
		
		bindLights(it->first, dirlights); // Ici on envoie les lumières aux programmes de shader
		//---------------------------------------------------
		
	}
}

void Scene::initUniformValue(const Program &program, const glm::mat4 &globalMVMatrix){

	//-----------------------------
	glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),1.f,0.1f,100.f);
	//-----------------------------

	glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVMatrix"), 1, GL_FALSE, glm::value_ptr(globalMVMatrix));
	glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uNormalMatrix"), 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(globalMVMatrix))));
	glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVPMatrix"), 1, GL_FALSE, glm::value_ptr(ProjMatrix * globalMVMatrix));
}
// ---------------------

