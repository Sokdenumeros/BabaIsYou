#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Menu.h"
#include <windows.h>
#include "Game.h"

Menu::Menu() {}

Menu::~Menu() {}

void Menu::init(string file) {
	time = 0;
	delay = 1000;
	text.init("fonts/segoepr.ttf");
	ifstream in;	
	currentTime = 0.0f;
	initShaders();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	in.open(file);
	int nbuttons, topY, topX, botY, botX;
	string name, texturefile;
	in >> nbuttons;
	buttons = vector<Button>(nbuttons);
	quads = vector<TexturedQuad*>(nbuttons);
	texs = vector<Texture>(nbuttons);
	glm::vec2 geom[2];
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	geom[0] = glm::vec2(0.f, 0.f);
	for (int i = 0; i < nbuttons; ++i) {
		in >> name >> texturefile >> topX >> topY >> botX >> botY;
		texs[i].loadFromFile(texturefile, TEXTURE_PIXEL_FORMAT_RGBA);
		geom[1] = glm::vec2(botX - topX, botY - topY);
		buttons[i].name = name;
		buttons[i].botX = botX;
		buttons[i].topX = topX;
		buttons[i].topY = topY;
		buttons[i].botY = botY;
		quads[i] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
		
	}
}

void Menu::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();


}

void Menu::update(int deltaTime) {
	currentTime += deltaTime;
	if (time > 0) time -= deltaTime;
	if (!Game::instance().getMouse()) time = 0;
	if (Game::instance().getMouse() && time < 1) {
		time = delay;
		int mousex = Game::instance().getMouseX();
		int mousey = Game::instance().getMouseY();
		for (int i = 0; i < buttons.size(); ++i) {
			if (buttons[i].topX < mousex && buttons[i].topY < mousey && buttons[i].botX > mousex && buttons[i].botY > mousey) {
				if (buttons[i].name == "Credits") {
					Game::instance().loadCredits();
				}
				else if (buttons[i].name == "Instructions") {
					Game::instance().loadInstructions();
				}
				else if (buttons[i].name == "MainMenu") {
					Game::instance().loadMenu();
				}
				else if (buttons[i].name == "Quit") {
					Game::instance().quit();
				}
			}
		}
	}
}

void Menu::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	int mousex = Game::instance().getMouseX();
	int mousey = Game::instance().getMouseY();
	for (int i = 0; i < quads.size(); ++i) {
		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(buttons[i].topX, buttons[i].topY, 0.f));
		if (buttons[i].topX < mousex && buttons[i].topY < mousey && buttons[i].botX > mousex && buttons[i].botY > mousey && buttons[i].name != "-") {
			float width = buttons[i].botX - buttons[i].topX;
			float height = buttons[i].botY - buttons[i].topY;
			modelview = glm::translate(modelview, glm::vec3(width/2, height/2, 0.f));
			modelview = glm::scale(modelview, glm::vec3(0.9f, 0.9f, 0.0f));
			modelview = glm::translate(modelview, glm::vec3(-width/2, -height/2, 0.f));
		}
		texProgram.setUniformMatrix4f("modelview", modelview);
		quads[i]->render(texs[i]);
	}
}