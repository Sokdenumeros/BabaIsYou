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
	int col, fil, maxfil, maxcol, tamany;

	ifstream inFile;
	inFile.open(level);
	inFile >> sound;
	inFile >> maxfil >> maxcol >> tilesize;
	int height = maxfil*tilesize, width = maxcol*tilesize;
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
	om = new ObjectMatrix(maxfil, maxcol, players);
	om->linkTempLists(&temp, &times);
	while (inFile >> tamany >> col >> fil) om->setPos(fil,col, new Player(players[tamany],fil,col));
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
		bool playfire = false;
		while (Pit != temp.end()) {
			(*Tit) -= deltaTime;
			(*Pit)->update(deltaTime);
			if ((*Tit) < 1) {
				if ((*Pit)->getname() == "foc") {
					int c = (*Pit)->getPosPlayerx()/ tilesize;
					int f = (*Pit)->getPosPlayery()/ tilesize;
					if (om->getPos(f + 1, c) != nullptr && om->getPos(f + 1, c)->getname() == "grass" && !om->getPos(f + 1, c)->itsname()) {fire(f + 1, c);playfire = true;}
					if (om->getPos(f - 1, c) != nullptr && om->getPos(f - 1, c)->getname() == "grass" && !om->getPos(f - 1, c)->itsname()) {fire(f - 1, c);playfire = true;}
					if (om->getPos(f, c + 1) != nullptr && om->getPos(f, c + 1)->getname() == "grass" && !om->getPos(f, c + 1)->itsname()) {fire(f, c + 1);playfire = true;}
					if (om->getPos(f, c - 1) != nullptr && om->getPos(f, c - 1)->getname() == "grass" && !om->getPos(f, c - 1)->itsname()) {fire(f, c - 1);playfire = true;}
				}
				delete (*Pit);
				temp.erase(Pit++);
				times.erase(Tit++);
			}
			else {
				++Pit;
				++Tit;
			}
		}
		if (playfire) AudioEngine::PlayS("audio/foc.mp3");
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
		vector<bool> positions (om->getNfil()*om->getNcol(),false);
		for (int i = 0, nfil = om->getNfil(); i < nfil; ++i) {
			for (int j = 0, ncol = om->getNcol(); j < ncol; ++j) {
				P = om->getPos(i, j);
				if (P != nullptr && P->getmove()) {
					if(j < ncol-1) positions[i*ncol + j + 1] = true;
					if(j > 0) positions[i*ncol + j - 1] = true;
					if(i < nfil-1) positions[i*ncol + j + ncol] = true;
					if(i > 0) positions[i*ncol + j - ncol] = true;
				}
			}
		}
		for (int i = 0, ncol = om->getNcol(); i < positions.size(); ++i) if(positions[i]) fire(i / ncol, i%ncol);
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

void Scene::fire(int f, int c) {
	if (f > -1 && f < om->getNfil() && c > -1 && c < om->getNcol()) {

		Player *p = nullptr;
		bool b = om->getPos(f, c) != nullptr && om->getPos(f, c)->getname() == "grass" && !om->getPos(f, c)->itsname();
		if (om->getPos(f, c) != nullptr && om->getPos(f, c)->gethasname() != "ningu") {
			searchaux(om->getPos(f, c)->gethasname(), false);
			p = new Player(aux, f, c);
		}
		if (om->getPos(f,c) != nullptr && om->getPos(f, c)->getname() == "is") om->deleteis(f, c);
		delete om->getPos(f, c); om->setPos(f, c, p);
		if (b) {
			searchaux("foc", false);
			temp.push_back(new Player(aux, f, c)); times.push_back(1000);
		}
		else {
			searchaux("explosio", false);
			temp.push_back(new Player(aux, f, c)); times.push_back(600);
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

