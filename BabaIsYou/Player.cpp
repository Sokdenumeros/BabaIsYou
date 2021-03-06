#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define velocitat 1

glm::ivec2 Player::tileMapDispl = glm::ivec2(1230, 1230);

enum PlayerAnims
{
	ANIMSTOP,STAND_LEFT, STAND_RIGHT,MOVE_UP1, MOVE_UP2, MOVE_UP3, MOVE_UP4, MOVE_UP5, MOVE_DOWN1, MOVE_DOWN2, MOVE_DOWN3, MOVE_DOWN4, MOVE_DOWN5, MOVE_LEFT1, MOVE_LEFT2, MOVE_LEFT3, MOVE_LEFT4, MOVE_LEFT5, MOVE_RIGHT1, MOVE_RIGHT2, MOVE_RIGHT3, MOVE_RIGHT4, MOVE_RIGHT5, STAND_UP, STAND_DOWN, MOVE_UP, MOVE_DOWN, ANIMATION
};

Player::Player(string nam, bool isnam, float sx, float sy, int mapx, int mapy, int ts)
{
	tilesize = ts;
	count = 0;
	move = false;
	name = nam;
	isname = isnam;
	sprx = sx;
	spry = sy;
	sink = false; win = false; push = false; defeat = false;
}

Player::Player(Player* P, int f, int c) {
	tilesize = P->tilesize;
	count = 0;
	name = P->name;
	isname = P->isname;
	sprx = P->sprx;
	spry = P->spry;
	sink = P->sink; win = P->win; push = P->push; defeat = P->defeat; move = P->move;
	posPlayer.x = c*tilesize; posPlayer.y = f*tilesize; spritesheet = P->spritesheet;
	init(*P->sprite->getShaderProgram(),P->spritesheet);
	setPosition(posPlayer); 
}

void Player::init(ShaderProgram &shaderProgram, Texture* ss)
{
	spritesheet = ss;
	sprite = Sprite::createSprite(glm::ivec2(tilesize, tilesize), glm::vec2(1.f / 32, 1.f / 64), spritesheet, &shaderProgram);

	if (name == "baba" && isname == false) {

		sprite->setNumberAnimations(40);


		sprite->setAnimationSpeed(STAND_LEFT, 5);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(11.f / 32, 0.f / 64));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(11.f / 32, 1.f / 64));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(11.f / 32, 2.f / 64));

		sprite->setAnimationSpeed(STAND_RIGHT, 5);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(1.f/32, 0.f/64));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(1.f / 32, 1.f / 64));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(1.f / 32, 2.f / 64));

		sprite->setAnimationSpeed(STAND_UP, 5);
		sprite->addKeyframe(STAND_UP, glm::vec2(6.f/32, 0.f/64));
		sprite->addKeyframe(STAND_UP, glm::vec2(6.f / 32, 1.f / 64));
		sprite->addKeyframe(STAND_UP, glm::vec2(6.f / 32, 2.f / 64));

		sprite->setAnimationSpeed(STAND_DOWN, 5);
		sprite->addKeyframe(STAND_DOWN, glm::vec2(16.f/32, 0.f/64));
		sprite->addKeyframe(STAND_DOWN, glm::vec2(16.f / 32, 1.f / 64));
		sprite->addKeyframe(STAND_DOWN, glm::vec2(16.f / 32, 2.f / 64));

		sprite->setAnimationSpeed(MOVE_LEFT1, 5);
		sprite->addKeyframe(MOVE_LEFT1, glm::vec2(10.f / 32, 0.f / 64));
		sprite->addKeyframe(MOVE_LEFT1, glm::vec2(10.f / 32, 1.f / 64));
		sprite->addKeyframe(MOVE_LEFT1, glm::vec2(10.f / 32, 2.f / 64));

		sprite->setAnimationSpeed(MOVE_LEFT2, 5);
		sprite->addKeyframe(MOVE_LEFT2, glm::vec2(11.f / 32, 0.f / 64));
		sprite->addKeyframe(MOVE_LEFT2, glm::vec2(11.f / 32, 1.f / 64));
		sprite->addKeyframe(MOVE_LEFT2, glm::vec2(11.f / 32, 2.f / 64));

		sprite->setAnimationSpeed(MOVE_LEFT3, 5);
		sprite->addKeyframe(MOVE_LEFT3, glm::vec2(12.f / 32, 0.f / 64));
		sprite->addKeyframe(MOVE_LEFT3, glm::vec2(12.f / 32, 1.f / 64));
		sprite->addKeyframe(MOVE_LEFT3, glm::vec2(12.f / 32, 2.f / 64));

		sprite->setAnimationSpeed(MOVE_LEFT4, 5);
		sprite->addKeyframe(MOVE_LEFT4, glm::vec2(13.f / 32, 0.f / 64));
		sprite->addKeyframe(MOVE_LEFT4, glm::vec2(13.f / 32, 1.f / 64));
		sprite->addKeyframe(MOVE_LEFT4, glm::vec2(13.f / 32, 2.f / 64));

		sprite->setAnimationSpeed(MOVE_LEFT5, 5);
		sprite->addKeyframe(MOVE_LEFT5, glm::vec2(14.f / 32, 0.f / 64));
		sprite->addKeyframe(MOVE_LEFT5, glm::vec2(14.f / 32, 1.f / 64));
		sprite->addKeyframe(MOVE_LEFT5, glm::vec2(14.f / 32, 2.f / 64));

		sprite->setAnimationSpeed(MOVE_RIGHT1, 5);
		sprite->addKeyframe(MOVE_RIGHT1, glm::vec2(0.f / 32, 0.f / 64));
		sprite->addKeyframe(MOVE_RIGHT1, glm::vec2(0.f / 32, 1.f / 64));
		sprite->addKeyframe(MOVE_RIGHT1, glm::vec2(0.f / 32, 2.f / 64));

		sprite->setAnimationSpeed(MOVE_RIGHT2, 5);
		sprite->addKeyframe(MOVE_RIGHT2, glm::vec2(1.f / 32, 0.f / 64));
		sprite->addKeyframe(MOVE_RIGHT2, glm::vec2(1.f / 32, 1.f / 64));
		sprite->addKeyframe(MOVE_RIGHT2, glm::vec2(1.f / 32, 2.f / 64));

		sprite->setAnimationSpeed(MOVE_RIGHT3, 5);
		sprite->addKeyframe(MOVE_RIGHT3, glm::vec2(2.f / 32, 0.f / 64));
		sprite->addKeyframe(MOVE_RIGHT3, glm::vec2(2.f / 32, 1.f / 64));
		sprite->addKeyframe(MOVE_RIGHT3, glm::vec2(2.f / 32, 2.f / 64));

		sprite->setAnimationSpeed(MOVE_RIGHT4, 5);
		sprite->addKeyframe(MOVE_RIGHT4, glm::vec2(3.f / 32, 0.f / 64));
		sprite->addKeyframe(MOVE_RIGHT4, glm::vec2(3.f / 32, 1.f / 64));
		sprite->addKeyframe(MOVE_RIGHT4, glm::vec2(3.f / 32, 2.f / 64));

		sprite->setAnimationSpeed(MOVE_RIGHT5, 5);
		sprite->addKeyframe(MOVE_RIGHT5, glm::vec2(4.f / 32, 0.f / 64));
		sprite->addKeyframe(MOVE_RIGHT5, glm::vec2(4.f / 32, 1.f / 64));
		sprite->addKeyframe(MOVE_RIGHT5, glm::vec2(4.f / 32, 2.f / 64));


		sprite->setAnimationSpeed(MOVE_UP1, 5);
		sprite->addKeyframe(MOVE_UP1, glm::vec2(5.f / 32, 0.f / 64));
		sprite->addKeyframe(MOVE_UP1, glm::vec2(5.f / 32, 1.f / 64));
		sprite->addKeyframe(MOVE_UP1, glm::vec2(5.f / 32, 2.f / 64));

		sprite->setAnimationSpeed(MOVE_UP2, 5);
		sprite->addKeyframe(MOVE_UP2, glm::vec2(6.f / 32, 0.f / 64));
		sprite->addKeyframe(MOVE_UP2, glm::vec2(6.f / 32, 1.f / 64));
		sprite->addKeyframe(MOVE_UP2, glm::vec2(6.f / 32, 2.f / 64));

		sprite->setAnimationSpeed(MOVE_UP3, 5);
		sprite->addKeyframe(MOVE_UP3, glm::vec2(7.f / 32, 0.f / 64));
		sprite->addKeyframe(MOVE_UP3, glm::vec2(7.f / 32, 1.f / 64));
		sprite->addKeyframe(MOVE_UP3, glm::vec2(7.f / 32, 2.f / 64));

		sprite->setAnimationSpeed(MOVE_UP4, 5);
		sprite->addKeyframe(MOVE_UP4, glm::vec2(8.f / 32, 0.f / 64));
		sprite->addKeyframe(MOVE_UP4, glm::vec2(8.f / 32, 1.f / 64));
		sprite->addKeyframe(MOVE_UP4, glm::vec2(8.f / 32, 2.f / 64));

		sprite->setAnimationSpeed(MOVE_UP5, 5);
		sprite->addKeyframe(MOVE_UP5, glm::vec2(9.f / 32, 0.f / 64));
		sprite->addKeyframe(MOVE_UP5, glm::vec2(9.f / 32, 1.f / 64));
		sprite->addKeyframe(MOVE_UP5, glm::vec2(9.f / 32, 2.f / 64));

		sprite->setAnimationSpeed(MOVE_DOWN1, 5);
		sprite->addKeyframe(MOVE_DOWN1, glm::vec2(15.f / 32, 0.f / 64));
		sprite->addKeyframe(MOVE_DOWN1, glm::vec2(15.f / 32, 1.f / 64));
		sprite->addKeyframe(MOVE_DOWN1, glm::vec2(15.f / 32, 2.f / 64));

		sprite->setAnimationSpeed(MOVE_DOWN2, 5);
		sprite->addKeyframe(MOVE_DOWN2, glm::vec2(16.f / 32, 0.f / 64));
		sprite->addKeyframe(MOVE_DOWN2, glm::vec2(16.f / 32, 1.f / 64));
		sprite->addKeyframe(MOVE_DOWN2, glm::vec2(16.f / 32, 2.f / 64));

		sprite->setAnimationSpeed(MOVE_DOWN3, 5);
		sprite->addKeyframe(MOVE_DOWN3, glm::vec2(17.f / 32, 0.f / 64));
		sprite->addKeyframe(MOVE_DOWN3, glm::vec2(17.f / 32, 1.f / 64));
		sprite->addKeyframe(MOVE_DOWN3, glm::vec2(17.f / 32, 2.f / 64));

		sprite->setAnimationSpeed(MOVE_DOWN4, 5);
		sprite->addKeyframe(MOVE_DOWN4, glm::vec2(18.f / 32, 0.f / 64));
		sprite->addKeyframe(MOVE_DOWN4, glm::vec2(18.f / 32, 1.f / 64));
		sprite->addKeyframe(MOVE_DOWN4, glm::vec2(18.f / 32, 2.f / 64));

		sprite->setAnimationSpeed(MOVE_DOWN5, 5);
		sprite->addKeyframe(MOVE_DOWN5, glm::vec2(19.f / 32, 0.f / 64));
		sprite->addKeyframe(MOVE_DOWN5, glm::vec2(19.f / 32, 1.f / 64));
		sprite->addKeyframe(MOVE_DOWN5, glm::vec2(19.f / 32, 2.f / 64));
		

		sprite->changeAnimation(STAND_RIGHT);
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	}

	//else if (name == "rock" && isname == false) { //if(o.getname() == "rock") {

		//sprite->setNumberAnimations(40);

		/*sprite->setAnimationSpeed(ANIMATION, 5);
		sprite->addKeyframe(ANIMATION, glm::vec2(4.f / 32, 27.f / 66));
		sprite->addKeyframe(ANIMATION, glm::vec2(5.f / 32, 28.f/ 66));
		sprite->addKeyframe(ANIMATION, glm::vec2(5.f / 32, 29.f / 66));


		sprite->changeAnimation(ANIMATION);
		*/

	//}

	else {

		sprite->setNumberAnimations(25);

		sprite->setAnimationSpeed(ANIMSTOP, 5);
		sprite->addKeyframe(ANIMSTOP, glm::vec2(sprx / 32, spry / 64));
		sprite->addKeyframe(ANIMSTOP, glm::vec2(sprx / 32, (spry + 1) / 64));
		sprite->addKeyframe(ANIMSTOP, glm::vec2(sprx / 32, (spry + 2) / 64));


		sprite->changeAnimation(ANIMSTOP);
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

	}
	int i = 0;
	++i;
}

void Player::update(int deltaTime) {
	sprite->update(deltaTime);
}

void Player::update(int deltaTime, int f, int c)
{
	if (posPlayer.x > c * tilesize) {
		posPlayer.x -= 2;
		if (name == "baba" && isname == false && posPlayer.x % 20 == 18) sprite->changeAnimation(MOVE_LEFT1 + (++count % 5));
	}
	if (posPlayer.x < c * tilesize) {
		posPlayer.x += 2;
		if (name == "baba" && isname == false && posPlayer.x % 20 == 2) sprite->changeAnimation(MOVE_RIGHT1 + (++count % 5));
	}
	if (posPlayer.y > f * tilesize) {
		posPlayer.y -= 2;
		if (name == "baba" && isname == false && posPlayer.y % 20 == 18) sprite->changeAnimation(MOVE_UP1 + (++count % 5));
	}
	if (posPlayer.y < f * tilesize) {
		posPlayer.y += 2;
		if (name == "baba" && isname == false && posPlayer.y%20 == 2) sprite->changeAnimation(MOVE_DOWN1 + (++count%5));
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite->update(deltaTime);
		
	}

void Player::up(int deltaTime)
{
	sprite->update(deltaTime);
}

void Player::render()
{
	sprite->render();
}

bool Player::getmove()
{
	return move;
}

void Player::setmove(bool b)
{
	move = b;
}

void Player::setpush(bool b)
{
	push = b;
}

void Player::sethasname(string s)
{
	hasname = s;
}

string Player::gethasname()
{
	return hasname;
}

void Player::setdefeat(bool b)
{
	defeat = b;
}

void Player::setwin(bool b)
{
	win = b;
}

void Player::setsink(bool b)
{
	sink = b;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

float Player::getposx()
{
	return sprx;
}

float Player::getposy()
{
	return spry;
}

string Player::getname()
{
	return name;
}

bool Player::itsname()
{
	return isname;
}

bool Player::getpush()
{
	return push||isname;
}

bool Player::getdefeat() {
	return defeat;
}

bool Player::getwin() {
	return win;
}

bool Player::getsink()
{
	return sink;
}

int Player::getPosPlayerx() {
	return posPlayer.x;
}

int Player::getPosPlayery() {
	return posPlayer.y;
}

void Player::setoffx(int x) { tileMapDispl.x = x; }

void Player::setoffy(int y) { tileMapDispl.y = y; }