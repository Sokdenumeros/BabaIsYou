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
	string TS;
	inFile >> TS;
	inFile >> tamany;
	Texture* T = new Texture();
	players.resize(tamany);
	players.clear();
	T->loadFromFile(TS, TEXTURE_PIXEL_FORMAT_RGBA);
	for (int i = 0; i < tamany; ++i) {
		inFile >> name >> isname >> posx >> posy;
		Player *P = new Player(name, isname, posx, posy, 0, 0);
		P->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, T);
		P->setPosition(glm::vec2(0,0));
		players.push_back(P);
	}
	om = new ObjectMatrix(sizex, sizey, players);
	while (inFile >> tamany >> mapx >> mapy) om->setPos(mapx,mapy, new Player(players[tamany],mapx*24,mapy*24));
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	aux = players[0];
	
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	if (!win) {
		auto Tit = times.begin();
		auto Pit = temp.begin();
		searchaux("foc", false);
		while (Pit != temp.end()) {
			(*Tit) -= deltaTime;
			(*Pit)->update(deltaTime);
			if ((*Tit) < 1) {
				if ((*Pit)->getname() == "foc") {
					int x = (*Pit)->getPosPlayerx()/24;
					int y = (*Pit)->getPosPlayery()/24;
					if (om->getPos(x + 1, y) != nullptr && om->getPos(x + 1, y)->getname() == "grass" && !om->getPos(x + 1, y)->itsname()) fire(x + 1, y);
					if (om->getPos(x - 1, y) != nullptr && om->getPos(x - 1, y)->getname() == "grass" && !om->getPos(x - 1, y)->itsname()) fire(x - 1, y);
					if (om->getPos(x, y + 1) != nullptr && om->getPos(x, y + 1)->getname() == "grass" && !om->getPos(x, y + 1)->itsname()) fire(x, y + 1);
					if (om->getPos(x, y - 1) != nullptr && om->getPos(x, y - 1)->getname() == "grass" && !om->getPos(x, y - 1)->itsname()) fire(x, y - 1);
				}
				temp.erase(Pit++);
				times.erase(Tit++);
			}
			else {
				++Pit;
				++Tit;
			}
		}
		om->update(deltaTime); //object matrix update
		win = om->getwin();
		if (win) time = currentTime;
	}
	if (win && currentTime - time > 2000) Game::instance().loadMenu();
	if (Game::instance().getKey(114)) Game::instance().loadLevel(lv);
	else if (Game::instance().getKey('m')) Game::instance().loadMenu();
	else if (Game::instance().getKey(' ') && !Game::instance().getutilitzat()) {
		AudioEngine::PlayS("explota.mp3");
		Game::instance().setutilitzat(true);
		Player* P;
		searchaux("foc", false);
		for (int i = 0; i < om->getNfil(); ++i) {
			for (int j = 0; j < om->getNcol(); ++j) {
				P = om->getPos(i, j);
				if (P != nullptr && P->getmove()) {
					fire(i + 1, j); fire(i - 1, j); fire(i, j + 1); fire(i, j - 1);
				}
			}
		}
	}
}

void Scene::searchaux(string name, bool isname) {
	if (aux->getname() == name) return;
	for (int i = 0; i < players.size(); ++i) 
		if (players[i]->getname() == name && players[i]->itsname() == isname) {
			aux = players[i];
			return;
	}
}

void Scene::fire(int i, int j) {
	if (i > -1 && i < om->getNfil() && j > -1 && j < om->getNcol()) {
		bool b = om->getPos(i, j) != nullptr && om->getPos(i, j)->getname() == "grass" && !om->getPos(i, j)->itsname();
		delete om->getPos(i, j); om->setPos(i, j, nullptr);
		if (b) {
			searchaux("foc", false);
			temp.push_back(new Player(aux, i * 24, j * 24)); times.push_back(1000);
		}
		else {
			searchaux("explosio", false);
			temp.push_back(new Player(aux, i * 24, j * 24)); times.push_back(600);
		}
	}
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
		for (auto it = temp.begin(); it != temp.end(); ++it) (*it)->render();
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

