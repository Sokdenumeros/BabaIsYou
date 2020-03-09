#pragma once
#include "Object.h"
#include <fstream>
#include "iostream"
using namespace std;

class ObjectMatrix {
public:
	ObjectMatrix();
	//bool setPosition(int x, int y, Object *o);
	vector<Object> getvec();
	int gettamany();
private:
	int sizex, sizey;
	//Object* map [];
	vector<Object> vec_obj;
	int tamany;
};