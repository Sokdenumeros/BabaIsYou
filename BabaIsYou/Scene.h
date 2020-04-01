
#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "ObjectMatrix.h"
#include <fstream>
#include "iostream"
#include "Text.h"
#include <list>
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
	void fire(int i, int j);
	string lv;
	void initShaders();
	ObjectMatrix* om;
	bool win;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	Text victory;
	int time;
	vector<Player*> players;
	list<Player*> temp;
	list<int> times;
	Player* aux;
	void searchaux(string name, bool isname);
};


#endif // _SCENE_INCLUDE

