
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

Player* ObjectMatrix::getPos(int f, int c) {
	if (f >= nf || c >= nc || f < 0 || c < 0) return nullptr;
	return matriu[f*nc + c];
}

ObjectMatrix::ObjectMatrix(int f, int c, vector<Player*>& v)
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

bool ObjectMatrix::recurs_players(int f, int c, movement m) {
	int current = nc*f + c;
	string sc, sn;
	switch (m) {
	case UP:
		f -= 1; break;
	case DOWN:
		f += 1; break;
	case LEFT:
		c -= 1; break;
	case RIGHT:
		c += 1; break;
	}
	if (f < 0 || f >= nf || c < 0 || c >= nc) return false;
	int next = nc*f +c;
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
					it->first = f; it->second = c;
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
		if (recurs_players(f, c, m)) {
			matriu[next] = matriu[current];
			matriu[current] = nullptr;
			if (matriu[next]->getname() == "is") {
				for (auto it = is.begin(); it != is.end(); ++it) {
					if (it->first == current / nc && it->second == current%nc) {
						it->first = f; it->second = c;
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

void ObjectMatrix::search_is(int f, int c, bool vertical)
{
	int right = !vertical ? nc*f+c+1 : nc*(f + 1) + c;
	int left = !vertical ? nc*f+c-1 : nc*(f - 1) + c;
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
			bool b = false;
			Player* p = nullptr;
			Player* puf = nullptr;
			for (int i = 0; i < players->size() && (p == nullptr || puf == nullptr); ++i) {
				if (!((*players)[i]->itsname()) && (*players)[i]->getname() == matriu[right]->getname()) p = (*players)[i];
				if (!((*players)[i]->itsname()) && (*players)[i]->getname() == "puf") puf = (*players)[i];
			}
			for (int i = 0; i < nc*nf; ++i) if (matriu[i] != nullptr && !matriu[i]->itsname() && matriu[i]->getname() == matriu[left]->getname()) {
				delete matriu[i];
				matriu[i] = new Player(p,i/nc,i%nc);
				temp->push_back(new Player(puf, i / nc, i%nc));
				times->push_back(600);
				b = true;
			}
			if (b) AudioEngine::PlayS("audio/poof.mp3");
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
		for (int i = 0; i < nf; ++i) {
			for (int j = nc-1; j >= 0; --j) {
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
		for (int i = nf-1; i >= 0; --i) {
			for (int j = 0; j < nc; ++j) {
				if (matriu[nc*i + j] != nullptr && matriu[nc*i + j]->getmove()) recurs_players(i, j, DOWN);
			}
		}
	}


	for (int i = 0; i < nf*nc; ++i) if (matriu[i] != nullptr) matriu[i]->update(deltaTime, i/nc, i%nc);
}

void ObjectMatrix::setPos(int f, int c, Player* p)
{
	if (f < nf && c < nc) {
		matriu[nc*f + c] = p;
		if (p!= nullptr && p->getname() == "is") 
			is.push_back(pair<int, int>(f, c));
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

void ObjectMatrix::linkTempLists(list<Player*>* p, list<int>* t) {
	temp = p;
	times = t;
}