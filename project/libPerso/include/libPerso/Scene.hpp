#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <map>
#include <array>
#include <cstring>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glimac/Image.hpp>

#include <libPerso/Program.hpp>
#include <libPerso/Mesh.hpp>
#include <libPerso/Texture.hpp>
#include <libPerso/Light.hpp>

class Scene 
{
	private:
		//std::vector<Mesh> meshes;
		std::vector<Texture> textures_loaded;
		std::map<Program, std::vector <Mesh>> mapMeshByShaders;
		std::string directory;

		// Créer une scéne à partir d'un fichier
		int loadScene(std::string path);
		// ---------------------
		
		// Parcourt des mesh
		void processNode(const aiNode* node, const aiScene* scene,  std::map<std::array<std::string, 2>, std::vector<Mesh>> &mapNameShader);
		// ---------------------
		
		// Chargement des Textures
		std::vector<Texture> processTexture(const aiMesh* aiMesh, const aiScene* scene, const aiMaterial *mat);
		std::vector<Texture> loadMaterialTextures(const aiMaterial* mat,const aiTextureType type, std::string typeName);
		// ---------------------
		
		// Gestion du map shader
		void addToMapShadersName(std::map<std::array<std::string, 2>,std::vector<Mesh>> &mapNameShader, const aiMaterial *mat, const Mesh mesh);
		std::string recoverNameShader (const std::string &nameMat, const std::string &begin, char end);
		void verifFileShaders (std::string &pathShader, const std::string &fileExtention);
		// ---------------------
		
		// Uniform value
		void initUniformValue(const Program &program, const glm::mat4 &globalMVMatrix);
		// ---------------------

	public:
		Scene();
		Scene(std::string path);
		
		~Scene();
		
		// Méthode de dessin
		void drawScene(const glm::mat4 &globalMVMatrix); 
		// ---------------------
};

#endif
