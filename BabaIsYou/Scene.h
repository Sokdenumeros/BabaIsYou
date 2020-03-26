
#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "ObjectMatrix.h"
#include <fstream>
#include "iostream"
#include "Text.h"
using namespace std;

// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init(string level);
	void update(int deltaTime);
	void render();
	bool getwin();

private:
	string lv;
	void initShaders();
	ObjectMatrix* om;
	//TileMap* map;
	//ObjectMatrix* om2;
	bool win;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	Text victory;
	int time;

};


#endif // _SCENE_INCLUDE

