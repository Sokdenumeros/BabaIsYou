#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"



void Game::init()
{
	credits.init("fonts/segoepr.ttf");
	loadMenu();
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
	case CREDITS:
		if(Game::instance().getKey('m')) loadMenu();
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
	case CREDITS:
		credits.render("JOAN MANEL FINESTRES BALDRICH", glm::vec2(220, 200), 70, glm::vec4(1, 1, 1, 1));
		credits.render("SERGI CURTO PANISELLO", glm::vec2(330, 400), 70, glm::vec4(1, 1, 1, 1));
		credits.render("[M] Menu", glm::vec2(600, 600), 40, glm::vec4(1, 1, 1, 1));
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
	scene.init(level);
}

void Game::loadCredits() {
	estat = CREDITS;
}

void Game::quit() {
	bPlay = false;
}

void Game::loadMenu() {
	estat = MAIN_MENU;
	menu.init("levels/MainMenu.txt");
}

void Game::setutilitzat(bool b)
{
	utilitzat = true;
}

