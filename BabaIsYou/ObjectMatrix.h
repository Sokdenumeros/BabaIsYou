#pragma once
#include <GL/glew.h>
#include <GL/glut.h>

#include <fstream>
#include "iostream"
#include "Player.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include <list>
using namespace std;

class ObjectMatrix 
{
private:
	bool win;
	Player **matriu;
	int nf, nc;
	enum movement { UP, DOWN, RIGHT, LEFT };
	bool recurs_players(int i, int j, movement m);
	int time, delay;
	vector<pair<int, int>> is;
	vector<Player*>* players;
	list<Player*>* temp;
	list<int>* times;
	

public:
	int getNcol();
	int getNfil();
	Player* getPos(int i, int j);
	ObjectMatrix(int f, int c, vector<Player*>& v);
	bool getwin();
	void update(int deltaTime);
	void setPos(int i, int j ,Player* p);
	void render();
	void search_is(int varx, int vary, bool vertical);
	void search_has(bool vertical);
	void explota(int pos);
	void linkTempLists(list<Player*>* p, list<int>* t);

};