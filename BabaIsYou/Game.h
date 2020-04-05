#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"
#include "AudioEngine.h"
#include "MainMenu.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

public:
	Game() {}
	
	
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	void loadLevel(string level);
	void quit();
	void loadCredits();
	void loadMenu();
	void loadInstructions();
	void setutilitzat(bool b);

	bool getMouse();
	bool getutilitzat();
	int getMouseX();
	int getMouseY();
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

private:
	Menu instructions, credits;
	MainMenu mainMenu;
	Scene scene;
	int mousex, mousey;
	bool mouse;
	enum STATE {LEVEL, MAIN_MENU, CREDITS, INSTRUCTIONS};
	STATE estat;
	bool bPlay;
	bool utilitzat = false;// Continue to play game?
	bool keys[256], specialKeys[256]; // Store key states so that 
	                                  // we can have access at any time

};


#endif // _GAME_INCLUDE


