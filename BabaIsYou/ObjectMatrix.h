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
	Player **matriu;
	int nf, nc;
	int is1x, is1y, is2x, is2y, is3x, is3y;
	enum movement { UP, DOWN, RIGHT, LEFT };
	bool recurs_players(int i, int j, movement m);

public:
	ObjectMatrix();
	void updat(int deltaTime);
	void ini(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int i, int j);
	void setPositio(const glm::vec2 &pos, int i, int j);
	void setPos(string nom, bool isname, float a, float b, int i, int j);
	void setTileMa(TileMap *tileMap, int i, int j);
	void rende();
	void search_is_dreta_esquerra(int varx, int vary);
	void search_is_esquerra_dreta(int varx, int vary);
	void search_is_adalt_abaix(int varx, int vary);
	void search_is_abaix_adalt(int varx, int vary);


};