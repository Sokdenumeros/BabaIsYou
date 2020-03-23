#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"



void Game::init()
{
	estat = MAIN_MENU;
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene.init("levels/mapa_sprite.txt");
	AudioEngine::Init();
	AudioEngine::PlayS("sao.mp3");
}

bool Game::update(int deltaTime)
{
	switch (estat) {
	case MAIN_MENU:
		break;
	case LEVEL:
		break;
	case WIN:
		break;
	case CREDITS:
		break;
	}
	scene.update(deltaTime);
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (estat) {
	case MAIN_MENU:
		break;
	case LEVEL:
		break;
	case WIN:
		break;
	case CREDITS:
		break;
	}
	scene.render();
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
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}





