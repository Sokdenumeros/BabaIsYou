#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define velocitat 1

enum PlayerAnims
{
	ANIMSTOP,STAND_LEFT, STAND_RIGHT,MOVE_UP1, MOVE_UP2, MOVE_UP3, MOVE_UP4, MOVE_UP5, MOVE_DOWN1, MOVE_DOWN2, MOVE_DOWN3, MOVE_DOWN4, MOVE_DOWN5, MOVE_LEFT1, MOVE_LEFT2, MOVE_LEFT3, MOVE_LEFT4, MOVE_LEFT5, MOVE_RIGHT1, MOVE_RIGHT2, MOVE_RIGHT3, MOVE_RIGHT4, MOVE_RIGHT5, STAND_UP, STAND_DOWN, MOVE_UP, MOVE_DOWN, ANIMATION
};



Player::Player(string nam, bool isnam, float sx, float sy, int mapx, int mapy)
{
name = nam;
isname = isnam;
sprx = sx;
spry = sy;
posmapax = mapx;
posmapay = mapy;
}


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{

	bJumping = false;
	spritesheet.loadFromFile("images/text.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(1.f / 32, 1.f / 66), &spritesheet, &shaderProgram);

	if (name == "baba" && isname == false) {
		//float a = o.getposx();

		

		sprite->setNumberAnimations(40);


		sprite->setAnimationSpeed(STAND_LEFT, 5);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(11.f / 32, 0.f / 66));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(11.f / 32, 1.f / 66));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(11.f / 32, 2.f / 66));

		sprite->setAnimationSpeed(STAND_RIGHT, 5);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(1.f/32, 0.f/66));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(1.f / 32, 1.f / 66));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(1.f / 32, 2.f / 66));

		sprite->setAnimationSpeed(STAND_UP, 5);
		sprite->addKeyframe(STAND_UP, glm::vec2(6.f/32, 0.f/66));
		sprite->addKeyframe(STAND_UP, glm::vec2(6.f / 32, 1.f / 66));
		sprite->addKeyframe(STAND_UP, glm::vec2(6.f / 32, 2.f / 66));

		sprite->setAnimationSpeed(STAND_DOWN, 5);
		sprite->addKeyframe(STAND_DOWN, glm::vec2(16.f/32, 0.f/66));
		sprite->addKeyframe(STAND_DOWN, glm::vec2(16.f / 32, 1.f / 66));
		sprite->addKeyframe(STAND_DOWN, glm::vec2(16.f / 32, 2.f / 66));

		sprite->setAnimationSpeed(MOVE_LEFT1, 5);
		sprite->addKeyframe(MOVE_LEFT1, glm::vec2(10.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_LEFT1, glm::vec2(10.f / 32, 1.f / 66));
		sprite->addKeyframe(MOVE_LEFT1, glm::vec2(10.f / 32, 2.f / 66));

		sprite->setAnimationSpeed(MOVE_LEFT2, 5);
		sprite->addKeyframe(MOVE_LEFT2, glm::vec2(11.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_LEFT2, glm::vec2(11.f / 32, 1.f / 66));
		sprite->addKeyframe(MOVE_LEFT2, glm::vec2(11.f / 32, 2.f / 66));

		sprite->setAnimationSpeed(MOVE_LEFT3, 5);
		sprite->addKeyframe(MOVE_LEFT3, glm::vec2(12.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_LEFT3, glm::vec2(12.f / 32, 1.f / 66));
		sprite->addKeyframe(MOVE_LEFT3, glm::vec2(12.f / 32, 2.f / 66));

		sprite->setAnimationSpeed(MOVE_LEFT4, 5);
		sprite->addKeyframe(MOVE_LEFT4, glm::vec2(13.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_LEFT4, glm::vec2(13.f / 32, 1.f / 66));
		sprite->addKeyframe(MOVE_LEFT4, glm::vec2(13.f / 32, 2.f / 66));

		sprite->setAnimationSpeed(MOVE_LEFT5, 5);
		sprite->addKeyframe(MOVE_LEFT5, glm::vec2(14.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_LEFT5, glm::vec2(14.f / 32, 1.f / 66));
		sprite->addKeyframe(MOVE_LEFT5, glm::vec2(14.f / 32, 2.f / 66));

		sprite->setAnimationSpeed(MOVE_RIGHT1, 5);
		sprite->addKeyframe(MOVE_RIGHT1, glm::vec2(0.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_RIGHT1, glm::vec2(0.f / 32, 1.f / 66));
		sprite->addKeyframe(MOVE_RIGHT1, glm::vec2(0.f / 32, 2.f / 66));

		sprite->setAnimationSpeed(MOVE_RIGHT2, 5);
		sprite->addKeyframe(MOVE_RIGHT2, glm::vec2(1.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_RIGHT2, glm::vec2(1.f / 32, 1.f / 66));
		sprite->addKeyframe(MOVE_RIGHT2, glm::vec2(1.f / 32, 2.f / 66));

		sprite->setAnimationSpeed(MOVE_RIGHT3, 5);
		sprite->addKeyframe(MOVE_RIGHT3, glm::vec2(2.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_RIGHT3, glm::vec2(2.f / 32, 1.f / 66));
		sprite->addKeyframe(MOVE_RIGHT3, glm::vec2(2.f / 32, 2.f / 66));

		sprite->setAnimationSpeed(MOVE_RIGHT4, 5);
		sprite->addKeyframe(MOVE_RIGHT4, glm::vec2(3.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_RIGHT4, glm::vec2(3.f / 32, 1.f / 66));
		sprite->addKeyframe(MOVE_RIGHT4, glm::vec2(3.f / 32, 2.f / 66));

		sprite->setAnimationSpeed(MOVE_RIGHT5, 5);
		sprite->addKeyframe(MOVE_RIGHT5, glm::vec2(4.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_RIGHT5, glm::vec2(4.f / 32, 1.f / 66));
		sprite->addKeyframe(MOVE_RIGHT5, glm::vec2(4.f / 32, 2.f / 66));


		sprite->setAnimationSpeed(MOVE_UP1, 5);
		sprite->addKeyframe(MOVE_UP1, glm::vec2(5.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_UP1, glm::vec2(5.f / 32, 1.f / 66));
		sprite->addKeyframe(MOVE_UP1, glm::vec2(5.f / 32, 2.f / 66));

		sprite->setAnimationSpeed(MOVE_UP2, 5);
		sprite->addKeyframe(MOVE_UP2, glm::vec2(6.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_UP2, glm::vec2(6.f / 32, 1.f / 66));
		sprite->addKeyframe(MOVE_UP2, glm::vec2(6.f / 32, 2.f / 66));

		sprite->setAnimationSpeed(MOVE_UP3, 5);
		sprite->addKeyframe(MOVE_UP3, glm::vec2(7.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_UP3, glm::vec2(7.f / 32, 1.f / 66));
		sprite->addKeyframe(MOVE_UP3, glm::vec2(7.f / 32, 2.f / 66));

		sprite->setAnimationSpeed(MOVE_UP4, 5);
		sprite->addKeyframe(MOVE_UP4, glm::vec2(8.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_UP4, glm::vec2(8.f / 32, 1.f / 66));
		sprite->addKeyframe(MOVE_UP4, glm::vec2(8.f / 32, 2.f / 66));

		sprite->setAnimationSpeed(MOVE_UP5, 5);
		sprite->addKeyframe(MOVE_UP5, glm::vec2(9.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_UP5, glm::vec2(9.f / 32, 1.f / 66));
		sprite->addKeyframe(MOVE_UP5, glm::vec2(9.f / 32, 2.f / 66));

		sprite->setAnimationSpeed(MOVE_DOWN1, 5);
		sprite->addKeyframe(MOVE_DOWN1, glm::vec2(15.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_DOWN1, glm::vec2(15.f / 32, 1.f / 66));
		sprite->addKeyframe(MOVE_DOWN1, glm::vec2(15.f / 32, 2.f / 66));

		sprite->setAnimationSpeed(MOVE_DOWN2, 5);
		sprite->addKeyframe(MOVE_DOWN2, glm::vec2(16.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_DOWN2, glm::vec2(16.f / 32, 1.f / 66));
		sprite->addKeyframe(MOVE_DOWN2, glm::vec2(16.f / 32, 2.f / 66));

		sprite->setAnimationSpeed(MOVE_DOWN3, 5);
		sprite->addKeyframe(MOVE_DOWN3, glm::vec2(17.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_DOWN3, glm::vec2(17.f / 32, 1.f / 66));
		sprite->addKeyframe(MOVE_DOWN3, glm::vec2(17.f / 32, 2.f / 66));

		sprite->setAnimationSpeed(MOVE_DOWN4, 5);
		sprite->addKeyframe(MOVE_DOWN4, glm::vec2(18.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_DOWN4, glm::vec2(18.f / 32, 1.f / 66));
		sprite->addKeyframe(MOVE_DOWN4, glm::vec2(18.f / 32, 2.f / 66));

		sprite->setAnimationSpeed(MOVE_DOWN5, 5);
		sprite->addKeyframe(MOVE_DOWN5, glm::vec2(19.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_DOWN5, glm::vec2(19.f / 32, 1.f / 66));
		sprite->addKeyframe(MOVE_DOWN5, glm::vec2(19.f / 32, 2.f / 66));
		

		sprite->changeAnimation(STAND_RIGHT);
		tileMapDispl = tileMapPos;
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
		sprite->addKeyframe(ANIMSTOP, glm::vec2(sprx / 32, spry / 66));
		sprite->addKeyframe(ANIMSTOP, glm::vec2(sprx / 32, (spry + 1) / 66));
		sprite->addKeyframe(ANIMSTOP, glm::vec2(sprx / 32, (spry + 2) / 66));


		sprite->changeAnimation(ANIMSTOP);
		tileMapDispl = tileMapPos;
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

	}
	
}

void Player::update(int deltaTime, int i, int j)
{
	//Player playnull("ningu", false, 0, 0, 0, 0);

	//Player *play = m[i][j];
				//if (play->getname() == "baba" && play->itsname() == false) {
					//if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
					//{
						//Game::instance().specialKeyReleased(GLUT_KEY_LEFT);
						//if (!movent) {
							//movent = false;
						//if (sprite->animation() != MOVE_LEFT)
						//if (m[i][j - 1]->getname() == "ningu") {
							//play->setmapy(j - 1);
							//m[i][j] =  new Player("ningu", false, 0, 0, 0, 0);
							//m[i][j - 1] = new Player("baba", false, 1, 1, i, j - 1);

						//}

	


						//if(i*loquesigui-posPlayer.x == 0) 
						//else //negativa posPlayer.x -= velocitat*deltaTime;
	if (posPlayer.x > i * 20) {
		posPlayer.x -= 2;
		if (name == "baba" && isname == false && posPlayer.x % 20 == 18) sprite->changeAnimation(MOVE_LEFT1 + (++count % 5));
	}
	if (posPlayer.x < i * 20) {
		posPlayer.x += 2;
		if (name == "baba" && isname == false && posPlayer.x % 20 == 2) sprite->changeAnimation(MOVE_RIGHT1 + (++count % 5));
	}
	if (posPlayer.y > j * 20) {
		posPlayer.y -= 2;
		if (name == "baba" && isname == false && posPlayer.y % 20 == 18) sprite->changeAnimation(MOVE_UP1 + (++count % 5));
	}
	if (posPlayer.y < j * 20) {
		posPlayer.y += 2;
		if (name == "baba" && isname == false && posPlayer.y%20 == 2) sprite->changeAnimation(MOVE_DOWN1 + (++count%5));
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite->update(deltaTime);
		/*if (name == "baba" && isname == false && pushed == false) {
			if (horitzontal == true && downright == true) {

				//if (i * 20 - posPlayer.x > 0) posPlayer.x += velocitat*deltaTime;
				//else posmapax = i;
				if (count == 0) sprite->changeAnimation(MOVE_RIGHT1);
				if (count == 1) sprite->changeAnimation(MOVE_RIGHT2);
				if (count == 2) sprite->changeAnimation(MOVE_RIGHT3);
				if (count == 3) sprite->changeAnimation(MOVE_RIGHT4);
				if (count == 4) sprite->changeAnimation(MOVE_RIGHT5);
				++count;
				if (count == 5) count = 0;

				if (posPlayer.x != i * 20) {
					posPlayer.x += 20;
				}
				posmapax = i;
			}

			else if (horitzontal == true && downright == false) {

				if (count == 0) sprite->changeAnimation(MOVE_LEFT1);
				if (count == 1) sprite->changeAnimation(MOVE_LEFT2);
				if (count == 2) sprite->changeAnimation(MOVE_LEFT3);
				if (count == 3) sprite->changeAnimation(MOVE_LEFT4);
				if (count == 4) sprite->changeAnimation(MOVE_LEFT5);
				++count;
				if (count == 5) count = 0;

				//if (i * 20 - posPlayer.x < 0) posPlayer.x -= velocitat*deltaTime;
				//else posmapax = i;
				if (posPlayer.x != i * 20) {
					posPlayer.x -= 20;
				}
				posmapax = i;
			}

			else if (horitzontal == false && downright == true) {

				if (count == 0) sprite->changeAnimation(MOVE_DOWN1);
				if (count == 1) sprite->changeAnimation(MOVE_DOWN2);
				if (count == 2) sprite->changeAnimation(MOVE_DOWN3);
				if (count == 3) sprite->changeAnimation(MOVE_DOWN4);
				if (count == 4) sprite->changeAnimation(MOVE_DOWN5);
				++count;
				if (count == 5) count = 0;
				//if (j * 20 - posPlayer.y > 0) posPlayer.y += velocitat*deltaTime;
				//else posmapay = j;
				if (posPlayer.y != j * 20) {
					posPlayer.y += 20;
				}
				posmapay = j;

			}

			else if (horitzontal == false && downright == false) {
				//if (j * 20 - posPlayer.y < 0) posPlayer.y -= velocitat*deltaTime;
				//else posmapay = j;
				if (count == 0) sprite->changeAnimation(MOVE_UP1);
				if (count == 1) sprite->changeAnimation(MOVE_UP2);
				if (count == 2) sprite->changeAnimation(MOVE_UP3);
				if (count == 3) sprite->changeAnimation(MOVE_UP4);
				if (count == 4) sprite->changeAnimation(MOVE_UP5);
				++count;
				if (count == 5) count = 0;
				if (posPlayer.y != j * 20) {
					posPlayer.y -= 20;
				}
				posmapay = j;
			}
		}

		else {
			if (horitzontal == true && downright == false) {

				if (posPlayer.x != i * 20) {
					posPlayer.x -= 20;
				}
				posmapax = i;
			}

			else if (horitzontal == true && downright == true) {

				if (posPlayer.x != i * 20) {
					posPlayer.x += 20;
				}
				posmapax = i;
			}


			else if (horitzontal == false && downright == false) {

				if (posPlayer.y != j * 20) {
					posPlayer.y -= 20;
				}
				posmapay = j;
			}

			else if (horitzontal == false && downright == true) {

				if (posPlayer.y != j * 20) {
					posPlayer.y += 20;
				}
				posmapay = j;
			}
		}


		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	/*while(i * 20 - posPlayer.x != 0) {

		if(i * 20 - posPlayer.x < 0) posPlayer.x -= velocitat*deltaTime;
		else posPlayer.x += velocitat*deltaTime;

		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
			}
		posmapax = i;
	
		while (j * 20 - posPlayer.y != 0) {

			if (j * 20 - posPlayer.y < 0) posPlayer.y -= velocitat*deltaTime;
			else posPlayer.y += velocitat*deltaTime;

			sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
		}
		posmapay = j;*/
			//else posPlayer.x -= velocitat*deltaTime;
							//posPlayer.x -= velocitat*deltaTime ;
							

						//movent = false;
					//}

					/*else if (Game::instance().getSpecialKey(GLUT_KEY_UP))
					{
						if (sprite->animation() != MOVE_UP)
							sprite->changeAnimation(MOVE_UP);
						posPlayer.y -= 2;
						if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
						{
							posPlayer.y += 2;
							sprite->changeAnimation(STAND_UP);
						}
					}
					else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
					{
						if (sprite->animation() != MOVE_DOWN)
							sprite->changeAnimation(MOVE_DOWN);
						posPlayer.y += 2;
						if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
						{
							posPlayer.y -= 2;
							sprite->changeAnimation(STAND_DOWN);
						}
					}
					else
					{
						//if (sprite->animation() == MOVE_LEFT)
							//sprite->changeAnimation(MOVE_LEFT);
						if (sprite->animation() == MOVE_RIGHT)
							sprite->changeAnimation(STAND_RIGHT);
						else if (sprite->animation() == MOVE_UP)
							sprite->changeAnimation(STAND_UP);
						else if (sprite->animation() == MOVE_DOWN)
							sprite->changeAnimation(STAND_DOWN);
					}*/
				//	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

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

void Player::setsink(bool b)
{
	sink = b;
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
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

int Player::getmapx()
{
	return posmapax;
}

int Player::getmapy()
{
	return posmapay;
}

bool Player::getpush()
{
	return push||isname;
}

bool Player::getsink()
{
	return sink;
}

void Player::setmapy(int j)
{
	posmapay = j;
}




