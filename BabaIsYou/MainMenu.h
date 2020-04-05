#include "Menu.h"

class MainMenu : public Menu {
public:
	MainMenu();
	~MainMenu();

	void init(string file);
	void update(int deltaTime);
	void render();

private:
	list<string>::iterator Lit;
	list<string> levels;
};
