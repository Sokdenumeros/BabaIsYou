#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"



void Game::init()
{
	credits.init("levels/credits.txt");
	loadMenu();
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	AudioEngine::Init();
	mouse = false;
}

bool Game::update(int deltaTime)
{
	if (keys['m']) loadMenu();
	AudioEngine::Update();
	switch (estat) {
	case MAIN_MENU:
		mainMenu.update(deltaTime);
		break;
	case LEVEL:
		scene.update(deltaTime);
		break;
	case CREDITS:
		credits.update(deltaTime);
		break;
	case INSTRUCTIONS:
		instructions.update(deltaTime);
		break;
	}
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (estat) {
	case MAIN_MENU:
		mainMenu.render();
		break;
	case LEVEL:
		scene.render();
		break;
	case CREDITS:
		credits.render();
		break;
	case INSTRUCTIONS:
		instructions.render();
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

bool Game::getutilitzat()
{
	return utilitzat;
}

int Game::getMouseX() {
	return mousex;
}

int Game::getMouseY() {
	return mousey;
}

void Game::loadLevel(string level) {
	utilitzat = false;
	estat = LEVEL;
	AudioEngine::StopAllChannels();
	scene.init(level);
}

void Game::loadCredits() {
	estat = CREDITS;
	credits.init("levels/Credits.txt");
}

void Game::quit() {
	bPlay = false;
}

void Game::loadMenu() {
	estat = MAIN_MENU;
	AudioEngine::StopAllChannels();
	mainMenu.init("levels/MainMenu.txt");
}

void Game::loadInstructions() {
	estat = INSTRUCTIONS;
	instructions.init("levels/Instructions.txt");
}

void Game::setutilitzat(bool b)
{
	utilitzat = true;
}

