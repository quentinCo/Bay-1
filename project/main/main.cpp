// Import lib C++
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

// Import SDL
#include <SDL/SDL.h>

// Import glimac
#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>

// Import GL
#include <GL/glew.h>

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

	// Verif existance fichier
	std::string pathFile = applicationPath.dirPath()+ "assets/models/scene_test.obj";
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
	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);  */
	
	Player player = Player(glm::vec3(0,1,-6), glm::vec3(0,0,2), 1.5, 0.02, 0.5);
	//std::cout <<"PLAYER : " << player << std::endl;
	
	//  --->  Ajout du player au monde des collisions.
	scene.addWorldCollision(player.getCollision());
// -----------------------

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

		glm::mat4 globalMVMatrix = player.getViewMatrixPlayer();
		
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
