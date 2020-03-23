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
	om->update(deltaTime); //object matrix update
	
	win = om->getwin();
		
	
	
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
	om->render();
		
	
	
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

bool Scene::getwin() {
	return win;
}

