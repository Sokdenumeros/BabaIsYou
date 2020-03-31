
#include "ObjectMatrix.h"
#include "Game.h"
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>





ObjectMatrix::ObjectMatrix(int c, int f, vector<Player*>& v)
{
	players = &v;
	nf = f;
	nc = c;
	matriu = new Player*[nf * nc];
	time = 0;
	delay = 200;
	for (int i = 0; i < nf*nc; ++i) {
		matriu[i] = nullptr;
	}
	win = false;
	
}

bool ObjectMatrix::recurs_players(int i, int j, movement m) {
	int current = nc*i + j;
	string sc, sn;
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
	if (matriu[current]->getsink()) {
		delete matriu[next];
		delete matriu[current];
		matriu[current] = nullptr;
		matriu[next] = nullptr;
		return true;
	}
	if (matriu[next] == nullptr) {
		matriu[next] = matriu[current];
		matriu[current] = nullptr;
		if (matriu[next]->getname() == "is") {
			for (auto it = is.begin(); it != is.end(); ++it) {
				if (it->first == current / nc && it->second == current%nc) {
					it->first = i; it->second = j;
				}
			}
		}
		return true;
	}
	if (matriu[next]->getsink()) {
		if (matriu[current]->getname() == "is") {
			for (auto it = is.begin(); it != is.end(); ++it) {
				if (it->first == current / nc && it->second == current%nc) is.erase(it);
			}
		}
		Player* pc = nullptr;
		Player* pn = nullptr;
		sc = matriu[current]->gethasname();
		sn = matriu[next]->gethasname();
		delete matriu[next];
		delete matriu[current];
		if(sc != "ningu") {
			for (int i = 0; i < nc*nf && pc == nullptr; ++i) if (matriu[i] != nullptr && !matriu[i]->itsname() && matriu[i]->getname() == sc) pc = matriu[i];
			
			matriu[current] = new Player(pc, (current / nc) * 24, (current%nc) * 24);
		}
		else matriu[current] = nullptr;

		if (sn != "ningu") {
			for (int i = 0; i < nc*nf && pn == nullptr; ++i) if (matriu[i] != nullptr && !matriu[i]->itsname() && matriu[i]->getname() == sn) pn = matriu[i];
			matriu[next] = new Player(pn, (next / nc) * 24, (next%nc) * 24);
		}
		else matriu[next] = nullptr;

		return true;
	}
	if (matriu[next]->getpush()) {
		if (recurs_players(i, j, m)) {
			matriu[next] = matriu[current];
			matriu[current] = nullptr;
			if (matriu[next]->getname() == "is") {
				for (auto it = is.begin(); it != is.end(); ++it) {
					if (it->first == current / nc && it->second == current%nc) {
						it->first = i; it->second = j;
					}
				}
			}
			return true;
		}
		else return false;
	}
	if (matriu[next]->getwin() && matriu[current]->getmove()) {
		AudioEngine::PlayS("victory.mp3");
		time = 600;
		win = true;
		delete matriu[next];
		matriu[next] = matriu[current];
		matriu[current] = nullptr;
		return true;
	}
	if (matriu[next]->getdefeat() && matriu[current]->getmove()) {
		Player* pd = nullptr;
		sc = matriu[current]->gethasname();
		delete matriu[current];
		if (sc != "ningu") {
			for (int i = 0; i < nc*nf && pd == nullptr; ++i) if (matriu[i] != nullptr && !matriu[i]->itsname() && matriu[i]->getname() == sc) pd = matriu[i];

			matriu[current] = new Player(pd, (current / nc) * 24, (current%nc) * 24);
		}
		else matriu[current] = nullptr;
		
		return true;
	}
	else return false;
}

void ObjectMatrix::search_is(int varx, int vary, bool vertical)
{

	int right = vertical ? nc*varx+vary+1 : nc*(varx + 1) + vary;
	int left = vertical ? nc*varx+vary-1 : nc*(varx - 1) + vary;
	if (right >= nc*nf || left < 0) return;
	if (matriu[left] != nullptr && matriu[right] != nullptr && matriu[left]->itsname() == true && matriu[right]->itsname() == true) {
		if (matriu[right]->getname() == "you") {
			for (int i = 0; i < 24; ++i) {
				for (int j = 0; j < 24; ++j) {
					if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getname() == matriu[left]->getname() && matriu[nc*i + j]->itsname() == false) {
						matriu[nc*i + j]->setmove(true);
					}
				}
			}
		}
		else if (matriu[right]->getname() == "push") {
			for (int i = 0; i < 24; ++i) {
				for (int j = 0; j < 24; ++j) {
					if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getname() == matriu[left]->getname() && matriu[nc*i + j]->itsname() == false) {
						matriu[nc*i + j]->setpush(true);
					}
				}
			}
		}
		else if (matriu[right]->getname() == "sink") {
			for (int i = 0; i < 24; ++i) {
				for (int j = 0; j < 24; ++j) {
					if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getname() == matriu[left]->getname() && matriu[nc*i + j]->itsname() == false) {
						matriu[nc*i + j]->setsink(true);
					}
				}
			}
		}
		else if (matriu[right]->getname() == "defeat") {
			for (int i = 0; i < 24; ++i) {
				for (int j = 0; j < 24; ++j) {
					if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getname() == matriu[left]->getname() && matriu[nc*i + j]->itsname() == false) {
						matriu[nc*i + j]->setdefeat(true);
					}
				}
			}
		}
		else if (matriu[right]->getname() == "win") {
			for (int i = 0; i < 24; ++i) {
				for (int j = 0; j < 24; ++j) {
					if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getname() == matriu[left]->getname() && matriu[nc*i + j]->itsname() == false) {
						matriu[nc*i + j]->setwin(true);
					}
				}
			}
		}
		else if (matriu[left]->getname() != "you" && matriu[left]->getname() != "push" &&matriu[left]->getname() != "sink" &&matriu[left]->getname() != "defeat" &&matriu[left]->getname() != "win" &&matriu[left]->getname() != "is"&&matriu[left]->getname() != "has"){
			Player* p = nullptr;
			for (int i = 0; i < players->size() && p == nullptr; ++i) if (!((*players)[i]->itsname()) && (*players)[i]->getname() == matriu[right]->getname()) p = (*players)[i];
			for (int i = 0; i < nc*nf; ++i) if (matriu[i] != nullptr && !matriu[i]->itsname() && matriu[i]->getname() == matriu[left]->getname()) {
				delete matriu[i];
				matriu[i] = new Player(p,(i/nc)*24,(i%nc)*24);
			}
		}
	}
}

void ObjectMatrix::search_has(bool vertical)
{
	
	for (int i = 0; i < 24; ++i) {
		for (int j = 0; j < 24; ++j) {
			if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getname() == "has") {
				int right = (vertical) ? nc*(i + 1) + j : nc*i + (j + 1);
				int left = (vertical) ? nc*(i - 1) + j : nc*i + (j - 1);
				if (matriu[right] != nullptr && matriu[left] != nullptr && matriu[left]->itsname() == true && matriu[right]->itsname() == true) {
					for (int i = 1; i < 23; ++i) {
						for (int j = 1; j < 23; ++j) {
							if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getname() == matriu[left]->getname() && matriu[nc*i + j]->itsname() == false) matriu[nc*i + j]->sethasname(matriu[right]->getname());
						}
					}
				}
			}
		}
	}
}

void ObjectMatrix::explota(int pos)
{
	Player* pd = nullptr;
	string s;

	if (matriu[pos] != nullptr) {
		s = matriu[pos]->gethasname();
		delete matriu[pos];

		for (int i = 0; i < nc*nf && pd == nullptr; ++i) if (matriu[i] != nullptr && !matriu[i]->itsname() && matriu[i]->getname() == "foc") pd = matriu[i];

		matriu[pos] = new Player(pd, (pos / nc) * 24, (pos%nc) * 24);

		if (s != "ningu") {
			for (int i = 0; i < nc*nf && pd == nullptr; ++i) if (matriu[i] != nullptr && !matriu[i]->itsname() && matriu[i]->getname() == s) pd = matriu[i];

			matriu[pos] = new Player(pd, (pos / nc) * 24, (pos%nc) * 24);
		}
		else matriu[pos] = nullptr;
	}
}


void ObjectMatrix::update(int deltaTime)
{

	
	
	string name;
	if (time > 0) time -= deltaTime;
	for (int i = 0; i < nf; ++i) {
		for (int j = 0; j < nc; ++j) {
			if (matriu[nc*i + j] != nullptr) {
				matriu[nc*i + j]->setsink(false);
				matriu[nc*i + j]->setpush(false);
				matriu[nc*i + j]->setdefeat(false);
				matriu[nc*i + j]->setwin(false);
				matriu[nc*i + j]->setmove(false);
				matriu[nc*i + j]->sethasname("ningu");
			}
		}
	}
	
	for (auto it = is.begin(); it != is.end(); ++it) {
		search_is(it->first, it->second,true);
		search_is(it->first, it->second,false);
	}

	search_has(false);
	search_has(true);
	
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && time < 1)
	{
		AudioEngine::PlayS("moviment.mp3");
		time = delay;
		for (int i = 0; i < nf; ++i) {
			for (int j = 0; j < nc; ++j) {
				if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getmove()) recurs_players(i, j, LEFT);
			}
		}
	}

	if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && time < 1)
	{
		AudioEngine::PlayS("moviment.mp3");
		time = delay;
		for (int i = nf-1; i >= 0; --i) {
			for (int j = 0; j < nc; ++j) {
				if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getmove()) recurs_players(i, j, RIGHT);
			}
		}
	}

	if (Game::instance().getSpecialKey(GLUT_KEY_UP) && time < 1)
	{
		AudioEngine::PlayS("moviment.mp3");
		time = delay;
		for (int i = 0; i < nf; ++i) {
			for (int j = 0; j < nc; ++j) {
				if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getmove()) recurs_players(i, j, UP);
			}
		}
	}

	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && time < 1)
	{
		AudioEngine::PlayS("moviment.mp3");
		time = delay;
		for (int i = 0; i < nf; ++i) {
			for (int j = nc-1; j >= 0; --j) {
				if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getmove()) recurs_players(i, j, DOWN);
			}
		}
	}

	if (Game::instance().getKey(32) == true && Game::instance().getutilitzat() == false)
	{
		AudioEngine::PlayS("explota.mp3");
		Game::instance().setutilitzat(true);
		int right, left, up, down;
		
		for (int i = 0; i < nf; ++i) {
			for (int j = nc - 1; j >= 0; --j) {
				if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getmove()) {
					right = nc*(i + 1) + j;
					left = nc*(i - 1) + j;
					up = nc*i + (j - 1);
					down = nc*i + (j + 1);

					explota(right);
					explota(left);
					explota(up);
					explota(down);
				}
			}
		}
	}


	for (int i = 0; i < nf; ++i) {
		for (int j = 0; j < nc; ++j) {
			if (matriu[nc*i + j] != nullptr) matriu[nc*i + j]->update(deltaTime, i, j);
		}
	}
}

void ObjectMatrix::setPos(int i, int j, Player* p)
{
	if (i < nf && j < nc) {
		matriu[nc*i + j] = p;
		if (p->getname() == "is") is.push_back(pair<int, int>(i, j));
	}
}

void ObjectMatrix::render()
{
	for (int i = 0; i < 24; ++i) {
		for (int j = 0; j < 24; ++j) {
			if (matriu[nc*i + j] != nullptr) {
				matriu[nc*i + j]->render();
			}
		}
	}
}

bool ObjectMatrix::getwin() {
	return win && (time < 1);
}

//els is que tenen a dreta i esquerra
