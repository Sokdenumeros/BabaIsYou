#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"



void Game::init()
{
	estat = MAIN_MENU;
	menu.init("levels/MainMenu.txt");
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	AudioEngine::Init();
	AudioEngine::PlayS("sao.mp3");
	mouse = false;
}

bool Game::update(int deltaTime)
{
	switch (estat) {
	case MAIN_MENU:
		menu.update(deltaTime);
		break;
	case LEVEL:
		scene.update(deltaTime);
		break;
	case WIN:
		break;
	case CREDITS:
		break;
	}
	
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (estat) {
	case MAIN_MENU:
		menu.render();
		break;
	case LEVEL:
		scene.render();
		break;
	case WIN:
		break;
	case CREDITS:
		break;
	}
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
	mousex = x;
	mousey = y;
}

void Game::mousePress(int button)
{
	mouse = true;
}

void Game::mouseRelease(int button)
{
	mouse = false;
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

bool Game::getMouse() {
	return mouse;
}

int Game::getMouseX() {
	return mousex;
}

int Game::getMouseY() {
	return mousey;
}

void Game::loadLevel(string level) {
	estat = LEVEL;
	scene.init(level);
}

void Game::quit() {
	bPlay = false;
}

