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
	map = NULL;
}

Scene::~Scene()
{
	if(map != NULL) delete map;
}


void Scene::init()
{
	initShaders();
	int tamany;
	map = TileMap::createTileMap("levels/mapa.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);	
	om = new ObjectMatrix(24,24);
	string name;
	bool isname;
	float posx, posy;
	int mapx, mapy;
	ifstream inFile;
	inFile.open("levels/mapa_sprite.txt");
	inFile >> tamany;
	for (int i = 0; i < tamany; ++i) {

		inFile >> name >> isname >> posx >> posy >> mapx >> mapy;
		
		om->setPos(name, isname, posx, posy, mapx, mapy);
		om->ini(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, mapx, mapy);
		om->setPositio(glm::vec2(mapx * map->getTileSize(), mapy *  map->getTileSize()), mapx, mapy);
		om->setTileMa(map, mapx,mapy);
		projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
		currentTime = 0.0f;
	}

	
		//un bucle per recorrer la matriu que haurem llegit, si es troba un numero anira al vector i pasara aquella posicio del vector a player init

			
		




		/*player1 = new Player();
		player1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, vo[1]);
		player1->setPosition(glm::vec2(10 * map->getTileSize(), 10 * map->getTileSize()));
		player1->setTileMap(map);
		projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
		currentTime = 0.0f;
	//}*/

	
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	om->updat(deltaTime); //object matrix update
		
	
	
	/*v_play[0].update(deltaTime, vo[0]);
	player1->update(deltaTime, vo[1]);
	*/
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();

	om->rende();
		
	
	
	//v_play[0].render();
	//player1->render();
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



