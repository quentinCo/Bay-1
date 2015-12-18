// Import lib C++
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

// Import glimac
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

// Import GL
#include <GL/glew.h>

// Import assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// Import gtest
#include <gtest/gtest.h>

// Import
#include <libPerso/Scene.hpp>

using namespace glimac;

int main(int argc, char** argv) {
/*
	bool printDebug;
	if(argc > 1 && std::string(argv[1]).compare("debug")==0){
		std::cout<<"MODE PRINT_DEBUG\n"<<std::endl;
		printDebug = true;
	}
	else{
		printDebug = false;
	}
*/
	// Initialize SDL and open a window
	SDLWindowManager windowManager(800, 800, "GLImac");

	// Initialize glew for OpenGL3+ support
	GLenum glewInitError = glewInit();
	if(GLEW_OK != glewInitError) {
		std::cerr << glewGetErrorString(glewInitError) << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

	/*********************************
	* HERE SHOULD COME THE INITIALIZATION CODE
	*********************************/
	
	// Shader
	FilePath applicationPath(argv[0]);

	// Chargement des shaders
	Program program = loadProgram(applicationPath.dirPath() + "shaders/test.vs.glsl", applicationPath.dirPath() + "shaders/test.fs.glsl");
	program.use();


	// Verif existance fichier
	//std::string pathFile = applicationPath.dirPath()+ "assets/models/nanosuit/nanosuit.obj";
	//std::string pathFile = applicationPath.dirPath()+ "assets/models/borderland/Lilith/Lilith.obj";
	std::string pathFile = applicationPath.dirPath()+ "assets/models/borderland/Maya_obj/maya_3.obj";
	//std::string pathFile = applicationPath.dirPath()+ "assets/models/forme_test_collor.obj";
	/*
	std::ifstream fin(pathFile.c_str());
	
	Assimp::Importer aImporter;
	
	if(!fin.fail()) {
		std::cout<< "Could open file: " << pathFile << std::endl;
		fin.close();
	}
	else{
		std::cerr<< "Couldn't open file: " << pathFile<<" \n" << aImporter.GetErrorString() << std::endl;
		return EXIT_FAILURE;
	}
	// ------------------------
	// Chargement scene
	const aiScene* aScene = aImporter.ReadFile(pathFile, aiProcess_Triangulate);
	if(aScene){
		std::cout << "Loading file : "<< pathFile <<std::endl;
	}
	else{
		std::cerr << "Error loading file : "<< pathFile <<" : " << aImporter.GetErrorString() <<std::endl;
		return EXIT_FAILURE;
	}
		
	// ------------------------
	// Print Test
	if(printDebug){
		std::cout << "INFORMATION MESHS CHARGES\n"<<std::endl;
		for(unsigned int i = 0; i < aScene->mNumMeshes; i++){
			std::cout << "Mesh : " << i << " - Adress : "<< aScene->mMeshes[i] << std::endl;
			std::cout << "Point du mesh :" << std::endl;
			for(unsigned int j = 0; j < aScene->mMeshes[i]->mNumVertices; j++){
				std::cout <<"----> [" << aScene->mMeshes[i]->mVertices[j].x
				<<" , "<< aScene->mMeshes[i]->mVertices[j].y
				<<" , "<< aScene->mMeshes[i]->mVertices[j].z
				<<"]"<< std::endl;
			}
			std::cout << "Face du mesh :"<< std::endl;
			for(unsigned int j = 0; j < aScene->mMeshes[i]->mNumFaces; j++){
				std::cout <<"Face "<< j <<" : "<<std::endl;
				for(unsigned int k = 0; k < aScene->mMeshes[i]->mFaces[j].mNumIndices; k++){
					std::cout <<"----> "<< aScene->mMeshes[i]->mFaces[j].mIndices[k]
					<< "[" << aScene->mMeshes[i]->mVertices[aScene->mMeshes[i]->mFaces[j].mIndices[k]].x
					<<" , "<< aScene->mMeshes[i]->mVertices[aScene->mMeshes[i]->mFaces[j].mIndices[k]].y
					<<" , "<< aScene->mMeshes[i]->mVertices[aScene->mMeshes[i]->mFaces[j].mIndices[k]].z;
					std::cout <<"]"<< std::endl;
				}
			}
			for(unsigned int j = 0; j < AI_MAX_NUMBER_OF_COLOR_SETS; j++){
			
				std::cout << "aiScene->mMeshes["<< i <<"]->HasVertexColors["<< j <<"]: "<< aScene->mMeshes[i]->HasVertexColors(j) <<"\n"<<std::endl;
				if( aScene->mMeshes[i]->HasVertexColors(j)){
					for(unsigned int k = 0; k < aScene->mMeshes[i]->mNumVertices; k++){
						std::cout <<  aScene->mMeshes[i]->mColors[j][k].r << " - " <<  aScene->mMeshes[i]->mColors[j][k].g << " - "<<  aScene->mMeshes[i]->mColors[j][k].b<<std::endl;
					}
				}
			}
		}
		std::cout << "\n--------------------------\n"<<std::endl;
	}
	// ------------------------
	
	// Init Scene
	std::cout << "CREATION SCENE" <<std::endl;
	std::vector <Mesh> scene;
	if(aScene->HasMeshes()){
		if(aScene->HasMaterials()){
			for(unsigned int i = 0; i < aScene->mNumMeshes; i++){
				scene.push_back(Mesh(
					aScene->mMeshes[i],
					aScene->mMaterials[aScene->mMeshes[i]->mMaterialIndex]
				));
			}
		}
		else{
			for(unsigned int i = 0; i < aScene->mNumMeshes; i++){
				scene.push_back(Mesh(aScene->mMeshes[i]));
			}
		}
	}
	*/
	Scene scene = Scene(pathFile.c_str());
	
	// ------------------------
	std::cout<< "CREATION SCENE FINI" << std::endl;
	
	glEnable(GL_DEPTH_TEST); 
	
	// Application loop:	
	bool done = false;
	while(!done) {
		// Event loop:
		SDL_Event e;
		while(windowManager.pollEvent(e)) {
			if(e.type == SDL_QUIT) {
				done = true; // Leave the loop after this iteration
			}
		}
		
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*********************************
		 * HERE SHOULD COME THE RENDERING CODE
		 *********************************/
	 	
		//for(auto it : scene) it.drawMesh(program);

		scene.drawScene(program);

		// Update the display
		windowManager.swapBuffers();
	}

	return EXIT_SUCCESS;
}
