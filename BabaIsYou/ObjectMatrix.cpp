
#include "ObjectMatrix.h"
#include "Game.h"
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>




ObjectMatrix::ObjectMatrix()
{
	nf = 24;
	nc = 24;
	matriu = new Player*[nf * nc];

	for (int i = 0; i < nf*nc; ++i) {
		matriu[i] = nullptr;
	}
	
}

bool ObjectMatrix::recurs_players(int i, int j, movement m) {
	int current = nc*i + j;
	switch (m) {
	case UP:
		j -= 1; break;
	case DOWN:
		j += 1; break;
	case LEFT:
		i -= 1; break;
	case RIGHT:
		i += 1; break;
	}
	if (j < 0 || j >= nf || i < 0 || i >= nc) return false;
	int next = nc*i +j;
	if (matriu[next] == nullptr) {
		matriu[next] = matriu[current];
		matriu[current] = nullptr;
		return true;
	}
	if (matriu[next]->getsink()) {
		delete matriu[next];
		delete matriu[current];
		matriu[current] = nullptr;
		matriu[next] = nullptr;
		return true;
	}
	if (matriu[next]->getpush()) {
		if (recurs_players(i, j, m)) {
			matriu[next] = matriu[current];
			matriu[current] = nullptr;
			if (matriu[next]->getname() == "is1") {
				is1x = i;
				is1y = j;
			}
			if (matriu[next]->getname() == "is2") {
				is2x = i;
				is2y = j;
			}
			if (matriu[next]->getname() == "is3") {
				is3x = i;
				is3y = j;
			}
			return true;
		}
		else return false;
	}
	else return false;
}

void ObjectMatrix::search_is_dreta_esquerra(int varx, int vary)
{
	if (matriu[nc*(varx + 1) + vary] != nullptr && matriu[nc*(varx + 1) + vary]->itsname() == true) {
		if (matriu[nc*(varx - 1) + vary] != nullptr && matriu[nc*(varx - 1) + vary]->getname() == "you") {
			for (int i = 0; i < 24; ++i) {
				for (int j = 0; j < 24; ++j) {
					if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getname() == matriu[nc*(varx + 1) + vary]->getname() && matriu[nc*i + j]->itsname() == false) {
						matriu[nc*i + j]->setmove(true);
					}
				}
			}
		}
		if (matriu[nc*(varx - 1) + vary] != nullptr && matriu[nc*(varx - 1) + vary]->getname() == "push") {
			for (int i = 0; i < 24; ++i) {
				for (int j = 0; j < 24; ++j) {
					if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getname() == matriu[nc*(varx + 1) + vary]->getname() && matriu[nc*i + j]->itsname() == false) {
						matriu[nc*i + j]->setpush(true);
					}
				}
			}
		}
		

	}
}

void ObjectMatrix::search_is_esquerra_dreta(int varx, int vary)
{
	if (matriu[nc*(varx - 1) + vary] != nullptr && matriu[nc*(varx - 1) + vary]->itsname() == true) {
		if (matriu[nc*(varx + 1) + vary] != nullptr && matriu[nc*(varx + 1) + vary]->getname() == "you") {
			for (int i = 0; i < 24; ++i) {
				for (int j = 0; j < 24; ++j) {
					if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getname() == matriu[nc*(varx - 1) + vary]->getname() && matriu[nc*i + j]->itsname() == false) {
						matriu[nc*i + j]->setmove(true);
					}
				}
			}
		}

		if (matriu[nc*(varx + 1) + vary] != nullptr && matriu[nc*(varx + 1) + vary]->getname() == "push") {
			for (int i = 0; i < 24; ++i) {
				for (int j = 0; j < 24; ++j) {
					if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getname() == matriu[nc*(varx - 1) + vary]->getname() && matriu[nc*i + j]->itsname() == false) {
						matriu[nc*i + j]->setpush(true);
					}
				}
			}
		}
		if (matriu[nc*(varx + 1) + vary] != nullptr && matriu[nc*(varx + 1) + vary]->getname() == "sink") {
			for (int i = 0; i < 24; ++i) {
				for (int j = 0; j < 24; ++j) {
					if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getname() == matriu[nc*(varx - 1) + vary]->getname() && matriu[nc*i + j]->itsname() == false) {
						matriu[nc*i + j]->setsink(true);
					}
				}
			}
		}

		
	}
}

void ObjectMatrix::search_is_adalt_abaix(int varx, int vary)
{
	if (matriu[nc*(varx)+(vary - 1)] != nullptr && matriu[nc*(varx)+(vary - 1)]->itsname() == true) {
		if (matriu[nc*(varx)+(vary + 1)] != nullptr && matriu[nc*(varx)+(vary + 1)]->getname() == "you") {
			for (int i = 0; i < 24; ++i) {
				for (int j = 0; j < 24; ++j) {
					if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getname() == matriu[nc*(varx)+(vary - 1)]->getname() && matriu[nc*i + j]->itsname() == false) {
						matriu[nc*i + j]->setmove(true);
					}
				}
			}
		}
		if (matriu[nc*(varx)+(vary + 1)] != nullptr && matriu[nc*(varx)+(vary + 1)]->getname() == "push") {
			for (int i = 0; i < 24; ++i) {
				for (int j = 0; j < 24; ++j) {
					if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getname() == matriu[nc*(varx)+(vary - 1)]->getname() && matriu[nc*i + j]->itsname() == false) {
						matriu[nc*i + j]->setpush(true);
					}
				}
			}
		}
		
	}
}

void ObjectMatrix::search_is_abaix_adalt(int varx, int vary)
{
	if (matriu[nc*(varx)+(vary + 1)] != nullptr && matriu[nc*(varx)+(vary + 1)]->itsname() == true) {
		if (matriu[nc*(varx)+(vary - 1)] != nullptr && matriu[nc*(varx)+(vary - 1)]->getname() == "you") {
			for (int i = 0; i < 24; ++i) {
				for (int j = 0; j < 24; ++j) {
					if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getname() == matriu[nc*(varx)+(vary + 1)]->getname() && matriu[nc*i + j]->itsname() == false) {
						matriu[nc*i + j]->setmove(true);
					}
				}
			}
		}
		if (matriu[nc*(varx)+(vary - 1)] != nullptr && matriu[nc*(varx)+(vary - 1)]->getname() == "push") {
			for (int i = 0; i < 24; ++i) {
				for (int j = 0; j < 24; ++j) {
					if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getname() == matriu[nc*(varx)+(vary + 1)]->getname() && matriu[nc*i + j]->itsname() == false) {
						matriu[nc*i + j]->setpush(true);
					}
				}
			}
		}
	}
}

void ObjectMatrix::updat(int deltaTime)
{

	for (int i = 0; i < nf; ++i) {
		for (int j = 0; j < nc; ++j) {
			if (matriu[nc*i + j] != nullptr) {
				matriu[nc*i + j]->setsink(false);
				matriu[nc*i + j]->setpush(false);
			}
		}
	}

	search_is_esquerra_dreta(is1x, is1y);
	search_is_dreta_esquerra(is1x, is1y);
	search_is_abaix_adalt(is1x, is1y);
	search_is_adalt_abaix(is1x, is1y);

	search_is_esquerra_dreta(is2x, is2y);
	search_is_dreta_esquerra(is2x, is2y);
	search_is_abaix_adalt(is2x, is2y);
	search_is_adalt_abaix(is2x, is2y);

	search_is_esquerra_dreta(is3x, is3y);
	search_is_dreta_esquerra(is3x, is3y);
	search_is_abaix_adalt(is3x, is3y);
	search_is_adalt_abaix(is3x, is3y);

	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		Game::instance().specialKeyReleased(GLUT_KEY_LEFT);
		for (int i = 0; i < nf; ++i) {
			for (int j = 0; j < nc; ++j) {
				if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getmove()) recurs_players(i, j, LEFT);
			}
		}
	}

	if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		Game::instance().specialKeyReleased(GLUT_KEY_RIGHT);
		for (int i = nf-1; i >= 0; --i) {
			for (int j = 0; j < nc; ++j) {
				if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getmove()) recurs_players(i, j, RIGHT);
			}
		}
	}

	if (Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		Game::instance().specialKeyReleased(GLUT_KEY_UP);
		for (int i = 0; i < nf; ++i) {
			for (int j = 0; j < nc; ++j) {
				if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getmove()) recurs_players(i, j, UP);
			}
		}
	}

	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		Game::instance().specialKeyReleased(GLUT_KEY_DOWN);
		for (int i = 0; i < nf; ++i) {
			for (int j = nc-1; j >= 0; --j) {
				if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getmove()) recurs_players(i, j, DOWN);
			}
		}
	}
	for (int i = 0; i < nf; ++i) {
		for (int j = 0; j < nc; ++j) {
			if (matriu[nc*i + j] != nullptr) matriu[nc*i + j]->update(deltaTime, i, j);
		}
	}
}

void ObjectMatrix::ini(const glm::ivec2 & tileMapPos, ShaderProgram & shaderProgram, int i, int j)
{
	matriu[nc*i + j]->init(tileMapPos, shaderProgram);
}

void ObjectMatrix::setPositio(const glm::vec2 & pos, int i, int j)
{
	matriu[nc*i + j]->setPosition(pos);
}

void ObjectMatrix::setPos(string nom, bool isname, float a, float b, int i, int j)
{
	matriu[nc*i + j] = new Player(nom, isname, a, b, i, j);
	if (nom == "is1") {
		is1x = i;
		is1y = j;
	}

	if (nom == "is2") {
		is2x = i;
		is2y = j;
	}

	if (nom == "is3") {
		is3x = i;
		is3y = j;
	}
}

void ObjectMatrix::setTileMa(TileMap *tileMap, int i, int j)
{
	matriu[nc*i + j]->setTileMap(tileMap);
}

void ObjectMatrix::rende()
{
	for (int i = 0; i < 24; ++i) {
		for (int j = 0; j < 24; ++j) {
			if (matriu[nc*i + j] != nullptr) {
				matriu[nc*i + j]->render();
			}
		}
	}
}

//els is que tenen a dreta i esquerra
