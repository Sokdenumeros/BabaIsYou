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
	currentTime = 0.0f;
	win = false;
	victory.init("fonts/segoepr.ttf");
	initShaders();
	
	string name; bool isname; float posx, posy;
	int mapx, mapy, sizex, sizey, tamany;

	ifstream inFile;
	inFile.open(level);
	inFile >> sound;
	inFile >> sizex >> sizey >> tilesize;
	int height = sizex*tilesize, width = sizey*tilesize;
	Player::setoffx((SCREEN_WIDTH-width)/2);
	Player::setoffy((SCREEN_HEIGHT - height) / 2);
	string TS;
	inFile >> TS >> tamany;
	Texture* T = new Texture();
	players.resize(tamany);
	players.clear();
	temp.clear();
	times.clear();
	T->loadFromFile(TS, TEXTURE_PIXEL_FORMAT_RGBA);
	for (int i = 0; i < tamany; ++i) {
		inFile >> name >> isname >> posx >> posy; 
		Player *P = new Player(name, isname, posx, posy, 0, 0, tilesize);
		P->init(texProgram, T);
		P->setPosition(glm::vec2(0,0));
		players.push_back(P);
	}
	om = new ObjectMatrix(sizex, sizey, players);
	while (inFile >> tamany >> mapx >> mapy) om->setPos(mapx,mapy, new Player(players[tamany],mapx,mapy));
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	aux = players[0];
	channel = AudioEngine::PlayS(sound);
}

void Scene::update(int deltaTime)
{
	if(!AudioEngine::IsPlaying(channel)) channel = AudioEngine::PlayS(sound);
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
					int x = (*Pit)->getPosPlayerx()/ tilesize;
					int y = (*Pit)->getPosPlayery()/ tilesize;
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
	else if (Game::instance().getKey(' ') && !Game::instance().getutilitzat()) {
		AudioEngine::PlayS("audio/explota.mp3");
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

		Player *p = nullptr;
		bool b = om->getPos(i, j) != nullptr && om->getPos(i, j)->getname() == "grass" && !om->getPos(i, j)->itsname();
		if (om->getPos(i, j) != nullptr && om->getPos(i, j)->gethasname() != "ningu") {
			searchaux(om->getPos(i, j)->gethasname(), false);
			p = new Player(aux, i, j);
		}
		delete om->getPos(i, j); om->setPos(i, j, p);
		if (b) {
			searchaux("foc", false);
			temp.push_back(new Player(aux, i, j)); times.push_back(1000);
		}
		else {
			searchaux("explosio", false);
			temp.push_back(new Player(aux, i, j)); times.push_back(600);
		}
	}
}

void Scene::render()
{

	if (win) {
		victory.render("VICTORY", glm::vec2(400, 400), 150, glm::vec4(1, 1, 1, 1));
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

