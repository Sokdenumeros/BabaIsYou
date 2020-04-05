#pragma once
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "ObjectMatrix.h"
#include <fstream>
#include "iostream"
#include "TexturedQuad.h"
#include <list>
#include "Text.h"


using namespace std;

// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Menu
{
public:
	Menu();
	~Menu();

	void init(string file);
	void update(int deltaTime);
	void render();

protected:
	struct Button { int topX, topY, botX, botY; string name; };
	vector<TexturedQuad*> quads;
	vector<Texture> texs;
	vector<Button> buttons;
	void initShaders();
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	Text text;
	int time, delay;
};
