#include "Game.h"

MainMenu::MainMenu() {}

MainMenu::~MainMenu() {}

void MainMenu::init(string file) {
	ifstream in;
	in.open("levels/index.txt");
	string level;
	while (in >> level) levels.push_back(level);
	in.close();
	Lit = levels.begin();
	Menu::init(file);
}

void MainMenu::render() {
	Menu::render();
	text.render(*Lit, glm::vec2(320, 400), 150, glm::vec4(1, 1, 1, 1));
}

void MainMenu::update(int deltaTime) {
	Menu::update(deltaTime);
	if (Game::instance().getMouse() && (time < 1||time == delay)) {
		int mousex = Game::instance().getMouseX();
		int mousey = Game::instance().getMouseY();
		for (int i = 0; i < buttons.size(); ++i) {
			if (buttons[i].topX < mousex && buttons[i].topY < mousey && buttons[i].botX > mousex && buttons[i].botY > mousey) {
				if (buttons[i].name == "RightArrow") {
					if (++Lit == levels.end()) Lit = levels.begin();
				}
				else if (buttons[i].name == "LeftArrow") {
					if (Lit == levels.begin()) Lit = levels.end();
					--Lit;
				}
				else if (buttons[i].name == "Play") {
					Game::instance().loadLevel("levels/" + *Lit + ".txt");
				}
			}
		}
	}
}