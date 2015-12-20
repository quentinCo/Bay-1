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
	const aiScene* aScene = aImporter.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	

	if(!aScene || aScene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !aScene->mRootNode){
		cerr<< "Couldn't open file: " << path<<" \n" << aImporter.GetErrorString() << std::endl;
		return EXIT_FAILURE;
	}
	else{
		cout << "File open : " << path << endl;
	}
	
	directory = path.substr(0, path.find_last_of('/'));

	processNode(aScene->mRootNode, aScene);
	
	return 1;
}
// ---------------------

// Parcours et initialisation des mesh
void Scene::processNode(const aiNode* aNode, const aiScene* aScene){
	for(GLuint i = 0; i < aNode->mNumMeshes; i++)
	{
		aiMesh* aMesh = aScene->mMeshes[aNode->mMeshes[i]];
	
		aiMaterial *mat;
	
		if(aScene->HasMaterials()) mat = aScene->mMaterials[aMesh->mMaterialIndex];
		else mat = NULL;


		Mesh mesh (aMesh, mat);
		
		mesh.setTextures(processTexture(aMesh, aScene, mat));
			
		meshes.push_back(mesh);		
	}

	for(GLuint i = 0; i < aNode->mNumChildren; i++) processNode(aNode->mChildren[i], aScene);
}
// ---------------------

// Initialisation des textures
vector<Texture> Scene::processTexture(const aiMesh* aiMesh, const aiScene* scene, const aiMaterial *mat){

	vector<Texture> textures;
	
	std::cout << "Load Texture : " <<std::endl;
	
	if(mat){
		std::vector<Texture> diffuseMaps = loadMaterialTextures(mat, aiTextureType_DIFFUSE, "Texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture> specularMaps = loadMaterialTextures(mat, aiTextureType_SPECULAR, "Texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	
		std::vector<Texture> ambiantMaps = loadMaterialTextures(mat, aiTextureType_AMBIENT , "Texture_ambiant");
		textures.insert(textures.end(), ambiantMaps.begin(), ambiantMaps.end());
	
		std::vector<Texture> emissiveMaps = loadMaterialTextures(mat, aiTextureType_EMISSIVE, "Texture_emissive");
		textures.insert(textures.end(), emissiveMaps.begin(), emissiveMaps.end());
	
		std::vector<Texture> normalMaps = loadMaterialTextures(mat, aiTextureType_HEIGHT , "Texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	
		std::vector<Texture> shininessMaps = loadMaterialTextures(mat, aiTextureType_SHININESS , "Texture_shininess");
		textures.insert(textures.end(), shininessMaps.begin(), shininessMaps.end());
	
		std::vector<Texture> opacityMaps = loadMaterialTextures(mat, aiTextureType_OPACITY , "Texture_opacity");
		textures.insert(textures.end(), opacityMaps.begin(), opacityMaps.end());
	} 
	
	return textures;
}


vector<Texture> Scene::loadMaterialTextures(const aiMaterial* mat,const aiTextureType type, std::string typeName){
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

// Dessin
void Scene::drawScene(const glimac::Program &prog){
	for(auto it : meshes) it.drawMesh(prog);
}
// ---------------------

