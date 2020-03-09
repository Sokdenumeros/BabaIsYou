#pragma once
#include "Object.h"
#include <fstream>
#include "iostream"
using namespace std;

class ObjectMatrix {
public:
	ObjectMatrix();
	bool setPosition(int x, int y, Object *o);
private:
	int sizex, sizey;
	Object* map [];
};