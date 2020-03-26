#pragma once
#include <GL/glew.h>
#include <GL/glut.h>

#include <fstream>
#include "iostream"
#include "Player.h"
#include "Texture.h"
#include "ShaderProgram.h"
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
	

public:
	ObjectMatrix(int f, int c);
	bool getwin();
	void update(int deltaTime);
	void setPos(int i, int j ,Player* p);
	void render();
	void search_is_esquerra_dreta(int varx, int vary);
	void search_is_adalt_abaix(int varx, int vary);


};