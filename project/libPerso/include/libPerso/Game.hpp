#ifndef GAME_H
#define GAME_H

#include <libPerso/Import.hpp>

class Game{
	private :
		// Singleton		
		static Game *instance;
		
		glimac::SDLWindowManager windowManager;
		
		Player player;
		
		std::string currentDir;
		
		Scene currentSite;
		
		std::map <std::string,SceneHeader> siteHeader;
		std::string firstSite;
		
		bool loopPlay;
		
		bool fullScreen;
		
		glm::mat4 ProjMatrix;
		
		int initOpenGLProperties();
		
		int initListeSite();
		
		void initNewCurrentSite(const SceneHeader &scene);
		
		void gameEvent();
				
		Game(std::string dir, std::string winName, uint32_t windowWidth, uint32_t windowHeight);
		
		~Game();
		
		
	public :
	
		static Game* getInstanceGame(
			std::string dir = "/",
			std::string winName = "Opengl",
			uint32_t windowWidth = 800,
			uint32_t windowHeight = 800
		);
				
		void gamePlay();
		
		
};

#endif
