#pragma once
#include "Sprite.h"
#include <string>

class Object {
public:
	Object(string nam, bool isnam, float sx, float sy);
	float getposx();
	float getposy();

private:
	float sprx, spry;
	Sprite* spr;
	string name;
	bool stop, push, win, defeat, skin;
	bool isname;
};