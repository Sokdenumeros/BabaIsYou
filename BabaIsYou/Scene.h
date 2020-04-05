
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
	void initShaders();
	void searchaux(string name, bool isname);

	float currentTime;
	string lv;
	bool win;
	int time;
	int tilesize;
	int channel;
	string sound;

	Text victory;
	ObjectMatrix* om;
	ShaderProgram texProgram;
	glm::mat4 projection;
	vector<Player*> players;
	list<Player*> temp;
	list<int> times;
	Player* aux;
};


#endif // _SCENE_INCLUDE

