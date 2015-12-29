// Import lib C++
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

// Import SDL
#include <SDL/SDL.h>

// Import glimac
#include <glimac/SDLWindowManager.hpp>
//#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

// Import GL
#include <GL/glew.h>
//#include <GL/glut.h>

// Import assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// Import gtest
#include <gtest/gtest.h>

// Import
#include <libPerso/Scene.hpp>
#include <libPerso/Player.hpp>
#include <libPerso/Program.hpp>

#define GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX 0x9048
#define GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX 0x9049


using namespace glimac;

int main(int argc, char** argv) {

	// Initialize SDL and open a window
	unsigned int windowWidth = 800;
	unsigned int windowHeight = 800;
	
	SDLWindowManager windowManager(windowWidth, windowHeight, "Bay-1");


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

	Program::setShadersDirectory(applicationPath.dirPath());

	// Chargement des shaders
/*
	Program program = loadProgram(applicationPath.dirPath() + "shaders/test.vs.glsl", applicationPath.dirPath() + "shaders/test.fs.glsl");
	program.use();
*/

	// Verif existance fichier
	std::string pathFile = applicationPath.dirPath()+ "assets/models/scene_test.obj";
	//std::string pathFile = applicationPath.dirPath()+ "assets/models/Cavern.obj";
	//std::string pathFile = applicationPath.dirPath()+ "assets/models/nanosuit/nanosuit.obj";
	//std::string pathFile = applicationPath.dirPath()+ "assets/models/borderland/Lilith/Lilith.obj";
	//std::string pathFile = applicationPath.dirPath()+ "assets/models/borderland/Maya_obj/maya_3.obj";
	//std::string pathFile = applicationPath.dirPath()+ "assets/models/forme_test_collor.obj";
	
// Init Scene
	std::cout << "CREATION SCENE" <<std::endl;

	Scene scene = Scene(pathFile.c_str());
// ------------------------

// Init Player (Player est herite de Camera)
	std::cout<< "CREATION SCENE FINI" << std::endl;
	
	glEnable(GL_DEPTH_TEST); 
	
	Player player = Player(glm::vec3(0,0,-6), glm::vec3(0,0,2), 0.05, 0.5);
	std::cout <<"CAMERA : " << player << std::endl;
// -----------------------
	
// Variable utiles pour la Camera
	
	//glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),1.f,0.1f,100.f);
// ------------------------------


/*
GLint total_mem_kb = 0;
glGetIntegerv(GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX, 
              &total_mem_kb);

GLint cur_avail_mem_kb = 0;
glGetIntegerv(GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX, 
              &cur_avail_mem_kb);
std::cout << "MEMOIR GPU => cur_avail_mem_kb / total_mem_kb : " << cur_avail_mem_kb << " / "<<total_mem_kb << std::endl;
*/

// Application loop:	
	bool loop = false;
	while(!loop) {
	// Traitement des events
		SDL_Event e;
				
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_QUIT){
				loop = true;
				break;
			}
			switch(e.type){
				case SDL_MOUSEMOTION:
					player.playerRotate(e.motion);
					break;

				case SDL_KEYDOWN:
					switch(e.key.keysym.sym){
						case SDLK_ESCAPE : 
							loop = true;
							break;
						default : break;
				}
				break;

				default:
				break;
			}		
		}
		
		// Gestion Deplacement (la touche reste enfoncé)
		Uint8 *keystate = SDL_GetKeyState(NULL);
		player.playerMove(keystate);
		
	// -------------------------------------------------------------------
		//std::cout <<"CAMERA : " << camera << std::endl;
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		/*********************************
		 * HERE SHOULD COME THE RENDERING CODE
		 *********************************/
	 	
		//for(auto it : scene) it.drawMesh(program);

		glm::mat4 globalMVMatrix = player.getViewMatrix();
		
		// Dessin
		scene.drawScene(globalMVMatrix);
		// ----------------------

		// Update the display
		windowManager.swapBuffers();
		/*
glGetIntegerv(GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX, 
              &total_mem_kb);

glGetIntegerv(GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX, 
              &cur_avail_mem_kb);
std::cout << "MEMOIR GPU => cur_avail_mem_kb / total_mem_kb : " << cur_avail_mem_kb << " / "<<total_mem_kb << std::endl;
		*/
	}

	return EXIT_SUCCESS;
}
