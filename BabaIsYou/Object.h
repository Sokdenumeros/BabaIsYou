#pragma once
#include "Sprite.h"
#include <string>

class Object {
public:
	Object(string nam, bool isnam, int sx, int sy);
private:
	int sprx, spry;
	Sprite* spr;
	string name;
	bool stop, push, win, defeat, skin;
	bool isname;
};