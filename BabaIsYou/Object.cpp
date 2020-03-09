#include "Object.h"

Object::Object(string nam, bool isnam, float sx, float sy)
{
	name = nam;
	isname = isnam;
	sprx = sx;
	spry = sy;
}

float Object::getposx()
{
	return spry;
}

float Object::getposy()
{
	return spry;
}
