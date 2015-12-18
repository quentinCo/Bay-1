#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <cstring>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glimac/Image.hpp>
#include <glimac/Program.hpp>

#include <libPerso/Mesh.hpp>
#include <libPerso/Texture.hpp>

class Scene 
{
	private:
		std::vector<Mesh> meshes;
		std::vector<Texture> textures_loaded;
		std::string directory;

		int loadScene(std::string path);
		void processNode(const aiNode* node, const aiScene* scene);
		std::vector<Texture> processTexture(const aiMesh* aiMesh, const aiScene* scene, const aiMaterial *mat);
		std::vector<Texture> loadMaterialTextures(const aiMaterial* mat,const aiTextureType type, std::string typeName);

	public:
		Scene();
		Scene(std::string path);
		
		~Scene();
		
		void drawScene(const glimac::Program &prog);  
};

#endif