#include "ObjectMatrix.h"



ObjectMatrix::ObjectMatrix() {
	string name;
	bool isname;
	float posx, posy;
	int mapx, mapy;
	ifstream inFile;
	inFile.open("levels/mapa_sprite.txt");
	inFile >> tamany;
	for (int i = 0; i < tamany; ++i) {

		inFile >> name >> isname >> posx >> posy >> mapx >> mapy;
		Object obj(name, isname, posx, posy, mapx, mapy);

		vec_obj.push_back(obj);

	}

	inFile.close();
}

/*bool ObjectMatrix::setPosition(int x, int y, Object* o) {
	if (map[x*sizey + y] == nullptr) map[x*sizey + y] = o;
	else return false;
	return true;
}*/

vector<Object> ObjectMatrix::getvec()
{
	return vec_obj;
}

int ObjectMatrix::gettamany()
{
	return tamany;
}
