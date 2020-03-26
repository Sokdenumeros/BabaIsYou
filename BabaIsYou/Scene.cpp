#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"



#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 6
#define INIT_PLAYER_Y_TILES 12


Scene::Scene()
{
	om = NULL;
}

Scene::~Scene()
{
	if(om != NULL) delete om;
}


void Scene::init(string level)
{
	lv = level;
	victory.init("fonts/OpenSans-Regular.ttf");
	currentTime = 0.0f;
	win = false;
	initShaders();
	ifstream inFile;
	inFile.open(level);
	string name;
	bool isname;
	float posx, posy;
	int mapx, mapy, sizex, sizey, tamany,tilesize;
	inFile >> sizex >> sizey >> tilesize;
	om = new ObjectMatrix(sizex, sizey);
	inFile >> tamany;
	Texture* T = new Texture();
	T->loadFromFile("images/text.png", TEXTURE_PIXEL_FORMAT_RGBA);
	for (int i = 0; i < tamany; ++i) {
		inFile >> name >> isname >> posx >> posy >> mapx >> mapy;
		Player* P = new Player(name, isname, posx, posy, mapx, mapy);
		P->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram,T);
		P->setPosition(glm::vec2(mapx * tilesize, mapy *  tilesize));
		om->setPos(mapx,mapy,P);	
	}
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	
}



void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	if (!win) {
		om->update(deltaTime); //object matrix update
		win = om->getwin();
		if (win) time = currentTime;
	}
	if (win && currentTime - time > 2000) Game::instance().loadMenu();
	if (Game::instance().getKey(114)) Game::instance().loadLevel(lv);

}

void Scene::render()
{

	if (win) {
		victory.render("Victory", glm::vec2(200, 200), 32, glm::vec4(1, 1, 1, 1));
	}
	else {
		glm::mat4 modelview;
		texProgram.use();
		texProgram.setUniformMatrix4f("projection", projection);
		texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
		modelview = glm::mat4(1.0f);
		texProgram.setUniformMatrix4f("modelview", modelview);
		texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
		om->render();
	}
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

bool Scene::getwin() {
	return win;
}

