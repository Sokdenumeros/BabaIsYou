
#include "ObjectMatrix.h"
#include "Game.h"
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>


bool different(string s) {
	return s != "you" && s != "push" && s != "sink" && s != "defeat" && s != "win" && s != "is"&& s != "has";
}

int ObjectMatrix::getNfil() { return nf; }

int ObjectMatrix::getNcol() { return nc; }

Player* ObjectMatrix::getPos(int i, int j) {
	if (i >= nf || j >= nc || i < 0 || j < 0) return nullptr;
	return matriu[i*nc + j];
}

ObjectMatrix::ObjectMatrix(int c, int f, vector<Player*>& v)
{
	players = &v;
	nf = f;
	nc = c;
	matriu = new Player*[nf * nc];
	time = 0;
	delay = 200;
	for (int i = 0; i < nf*nc; ++i) matriu[i] = nullptr;
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
			for (int i = 0; i < players->size() && pc == nullptr; ++i) if (!((*players)[i]->itsname()) && (*players)[i]->getname() == sc) pc = (*players)[i];
			
			matriu[current] = new Player(pc, (current / nc), (current%nc));
		}
		else matriu[current] = nullptr;

		if (sn != "ningu") {
			for (int i = 0; i < players->size() && pn == nullptr; ++i) if (!((*players)[i]->itsname()) && (*players)[i]->getname() == sn) pn = (*players)[i];
			matriu[next] = new Player(pn, (next / nc), (next%nc));
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
		AudioEngine::PlayS("audio/victory.mp3");
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

			for (int i = 0; i < players->size() && pd == nullptr; ++i) if (!((*players)[i]->itsname()) && (*players)[i]->getname() == sc) pd = (*players)[i];
			
				matriu[current] = new Player(pd, current / nc, current%nc);

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
	if (matriu[left] != nullptr && matriu[right] != nullptr && matriu[left]->itsname() == true && matriu[right]->itsname() == true && matriu[right]->getname() != "has" && matriu[left]->getname() != "has") {
		if (matriu[right]->getname() == "you") {
			for (int i = 0; i < nc*nf; ++i) {
				if (matriu[i] != nullptr && matriu[i]->getname() == matriu[left]->getname() && matriu[i]->itsname() == false) matriu[i]->setmove(true);
			}
		}
		else if (matriu[right]->getname() == "push") {
			for (int i = 0; i < nc*nf; ++i) {
				if (matriu[i] != nullptr && matriu[i]->getname() == matriu[left]->getname() && matriu[i]->itsname() == false) matriu[i]->setpush(true);
			}
		}
		else if (matriu[right]->getname() == "sink") {
			for (int i = 0; i < nc*nf; ++i) {
				if (matriu[i] != nullptr && matriu[i]->getname() == matriu[left]->getname() && matriu[i]->itsname() == false) matriu[i]->setsink(true);
			}
		}
		else if (matriu[right]->getname() == "defeat") {
			for (int i = 0; i < nc*nf; ++i) {
				if (matriu[i] != nullptr && matriu[i]->getname() == matriu[left]->getname() && matriu[i]->itsname() == false) matriu[i]->setdefeat(true);
			}
		}
		else if (matriu[right]->getname() == "win") {
			for (int i = 0; i < nc*nf; ++i) {
				if (matriu[i] != nullptr && matriu[i]->getname() == matriu[left]->getname() && matriu[i]->itsname() == false) matriu[i]->setwin(true);
			}
		}
		else if (different(matriu[left]->getname())){
			Player* p = nullptr;
			for (int i = 0; i < players->size() && p == nullptr; ++i) if (!((*players)[i]->itsname()) && (*players)[i]->getname() == matriu[right]->getname()) p = (*players)[i];
			for (int i = 0; i < nc*nf; ++i) if (matriu[i] != nullptr && !matriu[i]->itsname() && matriu[i]->getname() == matriu[left]->getname()) {
				delete matriu[i];
				matriu[i] = new Player(p,i/nc,i%nc);
			}
		}
	}
}

void ObjectMatrix::search_has(bool vertical)
{
	for (int i = 0; i < nf; ++i) {
		for (int j = 0; j < nc; ++j) {
			if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getname() == "has") {
				int right = (vertical) ? nc*(i + 1) + j : nc*i + (j + 1);
				int left = (vertical) ? nc*(i - 1) + j : nc*i + (j - 1);
				if (matriu[right] != nullptr && matriu[left] != nullptr && matriu[left]->itsname() == true && matriu[right]->itsname() == true && different(matriu[left]->getname()) && different(matriu[right]->getname())) {
					for (int ii = 0; ii < nf; ++ii) {
						for (int jj = 0; jj < nc; ++jj) {
							if (matriu[nc*ii + jj] != nullptr && matriu[nc*ii + jj]->getname() == matriu[left]->getname() && matriu[nc*ii + jj]->itsname() == false) matriu[nc*ii + jj]->sethasname(matriu[right]->getname());
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
		if (s != "ningu") {
			for (int i = 0; i < players->size() && pd == nullptr; ++i) if (!((*players)[i]->itsname()) && (*players)[i]->getname() == s) pd = (*players)[i];

			matriu[pos] = new Player(pd, (pos / nc), (pos%nc));
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
		AudioEngine::PlayS("audio/moviment.mp3");
		time = delay;
		for (int i = 0; i < nf; ++i) {
			for (int j = 0; j < nc; ++j) {
				if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getmove()) recurs_players(i, j, LEFT);
			}
		}
	}

	if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && time < 1)
	{
		AudioEngine::PlayS("audio/moviment.mp3");
		time = delay;
		for (int i = nf-1; i >= 0; --i) {
			for (int j = 0; j < nc; ++j) {
				if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getmove()) recurs_players(i, j, RIGHT);
			}
		}
	}

	if (Game::instance().getSpecialKey(GLUT_KEY_UP) && time < 1)
	{
		AudioEngine::PlayS("audio/moviment.mp3");
		time = delay;
		for (int i = 0; i < nf; ++i) {
			for (int j = 0; j < nc; ++j) {
				if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getmove()) recurs_players(i, j, UP);
			}
		}
	}

	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && time < 1)
	{
		AudioEngine::PlayS("audio/moviment.mp3");
		time = delay;
		for (int i = 0; i < nf; ++i) {
			for (int j = nc-1; j >= 0; --j) {
				if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getmove()) recurs_players(i, j, DOWN);
			}
		}
	}


	for (int i = 0; i < nf*nc; ++i) if (matriu[i] != nullptr) matriu[i]->update(deltaTime, i/nc, i%nc);
}

void ObjectMatrix::setPos(int i, int j, Player* p)
{
	if (i < nf && j < nc) {
		matriu[nc*i + j] = p;
		if (p!= nullptr && p->getname() == "is") is.push_back(pair<int, int>(i, j));
	}
}

void ObjectMatrix::render()
{
	for (int i = 0; i < nc*nf; ++i) if (matriu[i] != nullptr) matriu[i]->render();
}

bool ObjectMatrix::getwin() {
	return win && (time < 1);
}

//els is que tenen a dreta i esquerra
