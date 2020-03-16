
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
	int z = 9;
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
/*
bool ObjectMatrix::recurs_players_esquerra(int deltaTime, int i, int j) {

	if (matriu[nc*i + j] == nullptr) return true;
	else if ((matriu[nc*i + j]->itsname() == true && i > 0) || (matriu[nc*i + j]->getpush() == true && i > 0)) { //i - 1
		if (recurs_players_esquerra(deltaTime, i - 1, j) == true) {
			matriu[nc*(i-1)+j] = matriu[nc*(i) + j];
			//matriu[nc*(i-1)+j]->setmove(false);
			if (matriu[nc*(i - 1) + j]->getname() == "is1") {
				is1x = i - 1;
				is1y = j;
			}
			if (matriu[nc*(i - 1)+(j)]->getname() == "is2") {
				is2x = i - 1;
				is2y = j;
			}
			if (matriu[nc*(i - 1) + (j)]->getname() == "is3") {
				is3x = i - 1;
				is3y = j;
			}
			matriu[nc*(i) + j] = nullptr;
			matriu[nc*(i-1)+j]->update(deltaTime, i - 1, j, true, false, true);
			return true;
		}
	}
	else if (matriu[nc*i + j]->getsink() == true) {
		matriu[nc*(i + 1) + (j)]->update(deltaTime, 1000, j + 1, false, true, true);
		matriu[nc*(i + 1) + j] = nullptr;
		return false;
	}
	else return false;
}

bool ObjectMatrix::recurs_players_dreta(int deltaTime, int i, int j)
{
	if (matriu[nc*i + j] == nullptr) return true;
	else if ((matriu[nc*i + j]->itsname() == true && i < 23) || (matriu[nc*i + j]->getpush() == true && i < 23)) { //i - 1
		if (recurs_players_dreta(deltaTime, i + 1, j) == true) {
			matriu[nc*(i + 1) + j] = matriu[nc*(i)+j];
			//matriu[nc*(i-1)+j]->setmove(false);
			if (matriu[nc*(i + 1) + j]->getname() == "is1") {
				is1x = i + 1;
				is1y = j;
			}
			if (matriu[nc*(i + 1)+(j)]->getname() == "is2") {
				is2x = i + 1;
				is2y = j;
			}
			if (matriu[nc*(i + 1) + (j)]->getname() == "is3") {
				is3x = i + 1;
				is3y = j;
			}
			matriu[nc*(i)+j] = nullptr;
			matriu[nc*(i + 1) + j]->update(deltaTime, i + 1, j, true, true, true);
			return true;
		}
	}
	else if (matriu[nc*i + j]->getsink() == true) {
		matriu[nc*(i - 1) + (j)]->update(deltaTime, 1000, j + 1, false, true, true);
		matriu[nc*(i-1) + j] = nullptr;
		
		return false;
	}
	else return false;
}

bool ObjectMatrix::recurs_players_adalt(int deltaTime, int i, int j)
{
	if (matriu[nc*i + j] == nullptr) return true;
	else if ((matriu[nc*i + j]->itsname() == true && j > 0) || (matriu[nc*i + j]->getpush() == true && j > 0)) { //i - 1
		if (recurs_players_adalt(deltaTime, i, j-1) == true) {
			matriu[nc*(i) + (j-1)] = matriu[nc*(i)+j];
			//matriu[nc*(i-1)+j]->setmove(false);
			if (matriu[nc*(i) + (j-1)]->getname() == "is1") {
				is1x = i;
				is1y = j - 1;
			}
			if (matriu[nc*(i)+(j - 1)]->getname() == "is2") {
				is2x = i;
				is2y = j - 1;
			}
			if (matriu[nc*(i)+(j - 1)]->getname() == "is3") {
				is3x = i;
				is3y = j - 1;
			}
			matriu[nc*(i)+j] = nullptr;
			matriu[nc*(i) + (j-1)]->update(deltaTime, i, j - 1, false, false, true);
			return true;
		}
	}
	else if (matriu[nc*i + j]->getsink() == true) {
		matriu[nc*(i)+(j + 1)]->update(deltaTime, 1000, j + 1, false, true, true);
		matriu[nc*i + j + 1] = nullptr;
		
		return false;
	}
	else return false;
}

bool ObjectMatrix::recurs_players_abaix(int deltaTime, int i, int j)
{
	if (matriu[nc*i + j] == nullptr) return true;
	else if ((matriu[nc*i + j]->itsname() == true && j < 23) || (matriu[nc*i + j]->getpush() == true && j < 23)) { //i - 1
		if (recurs_players_abaix(deltaTime, i, j + 1) == true) {
			matriu[nc*(i)+(j + 1)] = matriu[nc*(i)+j];
			//matriu[nc*(i-1)+j]->setmove(false);
			if (matriu[nc*(i)+(j + 1)]->getname() == "is1") {
				is1x = i;
				is1y = j + 1;
			}
			if (matriu[nc*(i)+(j + 1)]->getname() == "is2") {
				is2x = i;
				is2y = j + 1;
			}
			if (matriu[nc*(i)+(j + 1)]->getname() == "is3") {
				is3x = i;
				is3y = j + 1;
			}
			matriu[nc*(i)+j] = nullptr;
			matriu[nc*(i)+(j + 1)]->update(deltaTime, i, j + 1, false, true, true);
			return true;
		}
	}
	else if (matriu[nc*i + j]->getsink() == true) {
		matriu[nc*(i)+(j - 1)]->update(deltaTime, 1000, j + 1, false, true, true);
		matriu[nc*i + j - 1] = nullptr;
		
		return false;
	}
	else return false;
}
*/
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
	/*if (m[x][y].name == you) {
		m[x][y + 1] = m[x][y];
		m[x][y]->update(deltaTime, x, y);
	}*/

	for (int i = 0; i < 24; ++i) {
		for (int j = 0; j < 24; ++j) {
			if (matriu[nc*i + j] != nullptr) {
				matriu[nc*i + j]->setsink(false);
				matriu[nc*i + j]->setpush(false);
				matriu[nc*i + j]->update(deltaTime,i,j);
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
	/*
	movement m = NONE;
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		Game::instance().specialKeyReleased(GLUT_KEY_LEFT);
		m = LEFT;
	}
	if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		Game::instance().specialKeyReleased(GLUT_KEY_RIGHT);
		m = RIGHT;
	}
	if (Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		Game::instance().specialKeyReleased(GLUT_KEY_UP);
		m = UP;
	}
	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		Game::instance().specialKeyReleased(GLUT_KEY_DOWN);
		m = DOWN;
	}
	if (m != NONE) {
		for (int i = 0; i < 24; ++i) {
			for (int j = 0; j < 24; ++j) {
				if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getmove()) {

					if (i > 0) {
						if (recurs_players_esquerra(deltaTime, i - 1, j) == true) {
							matriu[nc*(i - 1) + j] = matriu[nc*i + j];
							matriu[nc*(i - 1) + j]->setmove(false);
							matriu[nc*i + j] = nullptr;
							matriu[nc*(i - 1) + j]->update(deltaTime, i - 1, j, true, false, false);
						}
					}
				}
			}
		}
	}
	*/
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		Game::instance().specialKeyReleased(GLUT_KEY_LEFT);
		for (int i = 0; i < 24; ++i) {
			for (int j = 0; j < 24; ++j) {
				if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getmove()) recurs_players(i, j, LEFT);
			}
		}
	}

	if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		Game::instance().specialKeyReleased(GLUT_KEY_RIGHT);
		for (int i = 23; i >= 0; --i) {
			for (int j = 0; j < 24; ++j) {
				if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getmove()) recurs_players(i, j, RIGHT);
			}
		}
	}

	if (Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		Game::instance().specialKeyReleased(GLUT_KEY_UP);
		for (int i = 0; i < 24; ++i) {
			for (int j = 0; j < 24; ++j) {
				if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getmove()) recurs_players(i, j, UP);
			}
		}
	}

	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		Game::instance().specialKeyReleased(GLUT_KEY_DOWN);
		for (int i = 0; i < 24; ++i) {
			for (int j = 23; j >= 0; --j) {
				if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getmove()) recurs_players(i, j, DOWN);
			}
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

/*bool ObjectMatrix::setPosition(int x, int y, Object* o) {
	if (map[x*sizey + y] == nullptr) map[x*sizey + y] = o;
	else return false;
	return true;
}

void ObjectMatrix::setPos(Player p)
{
	matriu[p.getmapx()][p.getmapy()] = p;
}

Player[20][20] ObjectMatrix::getmat()
{
	return matriu;
}

void ObjectMatrix::setMat(vector<vector<Player>> m) {
	matriu = m;
}

int ObjectMatrix::gettamany()
{
	return tamany;
}
*/

//els is que tenen a dreta i esquerra
