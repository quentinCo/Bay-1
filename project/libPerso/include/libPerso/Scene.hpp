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
#include <libPerso/Light_impl.hpp>

class Scene 
{
	private:
		// Textures de la scene et mesh triés par shader
		std::vector<Texture> textures_loaded;
		std::map<Program, std::vector <Mesh>> mapMeshByShaders;
		
		// Repertoire current de l'application
		std::string directory;
		
		// Liste des lumières
		std::vector <EllipsoidLight> vectorLights;
		EllipsoidLight *lights;
		LightBuffer <EllipsoidLight> lightsBuffer;
		
		std::vector <DirectionalLight> vectorDirLights;
		DirectionalLight *dirLights;
		LightBuffer <DirectionalLight> dirLightsBuffer;
		
		// Information sur la camera.
		glm::vec3 cameraPosition;
		glm::vec3 cameraFront;
		
		// Chemin vers les autres sites
		std::string nextSites[2];
		
		// Evite la suppression accidentel des variables allouées avec la destruction de copie.
		// Même méthode que pour les copies des Bufferset VAO.
		unsigned int id;
		static std::map<unsigned int, unsigned int> occurenceCounter;
		static unsigned int occurence;
		
		// FONCTIONS
		// Créer une scéne à partir d'un fichier
		int loadScene(const std::string path);
		// ---------------------
		
		// Parcourt des mesh
		void processNode(const aiNode* node, const aiScene* scene,  std::map<std::array<std::string, 2>, std::vector<Mesh>> &mapNameShader);
		// ---------------------
		
		// Chargement des Textures
		std::vector<Texture> processTexture(const aiMesh* aiMesh, const aiScene* scene, const aiMaterial *mat);
		std::vector<Texture> loadMaterialTextures(const aiMaterial* mat,const aiTextureType type, std::string typeName);
		// ---------------------
		
		// Gestion du map shader
		void addToMapShadersName(std::map<std::array<std::string, 2>,std::vector<Mesh>> &mapNameShader, const aiMaterial *mat, const Mesh &mesh);
		std::string recoverNameShader (const std::string &nameMat, const std::string &begin, char end);
		void verifFileShaders (std::string &pathShader, const std::string &fileExtention);
		// ---------------------
		
		// Uniform value
		void initUniformValue(const Program &program, const glm::mat4 &globalMVMatrix);
		void initUniformLightTabs();
		// ---------------------

	public:
		Scene();
		Scene(const std::string path, const std::string next[]);
		Scene(const Scene &s);
		
		Scene& operator =(Scene&& rvalue);
		
		~Scene();
		
		glm::vec3 getCameraPosition() const ;
		glm::vec3 getCameraFront() const;
		std::string getNext(int i) const;
		
		// Méthode de dessin
		void drawScene(const glm::mat4 &globalMVMatrix); 
		// ---------------------
		
};

#endif
