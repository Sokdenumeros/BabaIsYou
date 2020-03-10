#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, STAND_UP, STAND_DOWN, MOVE_UP, MOVE_DOWN, ANIMATION, ANIMSTOP
};


Player::Player()
{
}

void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, Object o)
{

	float a = o.getposx();
	float b = o.getposy();
	bJumping = false;
	spritesheet.loadFromFile("images/text.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(1.f / 32, 1.f / 66), &spritesheet, &shaderProgram);

	
	if (o.getname() == "baba" && o.itsname() == false) {
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

		sprite->setAnimationSpeed(MOVE_LEFT, 5);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(10.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(11.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(12.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(13.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(14.f / 32, 0.f / 66));

		sprite->setAnimationSpeed(MOVE_RIGHT, 5);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(2.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(3.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(4.f / 32, 0.f / 66));


		sprite->setAnimationSpeed(MOVE_UP, 5);
		sprite->addKeyframe(MOVE_UP, glm::vec2(5.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_UP, glm::vec2(6.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_UP, glm::vec2(7.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_UP, glm::vec2(8.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_UP, glm::vec2(9.f / 32, 0.f / 66));

		sprite->setAnimationSpeed(MOVE_DOWN, 5);
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(15.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(16.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(17.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(18.f / 32, 0.f / 66));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(19.f / 32, 0.f / 66));

		sprite->changeAnimation(STAND_RIGHT);
		tileMapDispl = tileMapPos;
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	}

	/*else { //if(o.getname() == "rock") {



		bJumping = false;
		spritesheet.loadFromFile("images/text.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(o.getposx() / 32, o.getposy() / 66), &spritesheet, &shaderProgram);

		//sprite->setNumberAnimations(40);

		/*sprite->setAnimationSpeed(ANIMATION, 5);
		sprite->addKeyframe(ANIMATION, glm::vec2(4.f / 32, 27.f / 66));
		sprite->addKeyframe(ANIMATION, glm::vec2(5.f / 32, 28.f/ 66));
		sprite->addKeyframe(ANIMATION, glm::vec2(5.f / 32, 29.f / 66));


		sprite->changeAnimation(ANIMATION);

	}*/

	else {


		

		sprite->setNumberAnimations(25);

		sprite->setAnimationSpeed(ANIMSTOP, 5);
		sprite->addKeyframe(ANIMSTOP, glm::vec2(a / 32, b / 66));
		sprite->addKeyframe(ANIMSTOP, glm::vec2(a / 32, (b + 1) / 66));
		sprite->addKeyframe(ANIMSTOP, glm::vec2(a / 32, (b + 2) / 66));


		sprite->changeAnimation(ANIMSTOP);

	}
	
}

void Player::update(int deltaTime, Object o)
{
	sprite->update(deltaTime);
	if (o.getname() == "baba" && o.itsname() == false) {
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
		{
			//if (!movent) {
				//movent = false;
			if (sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
	
			posPlayer.x -= 2;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.x += 2;
				sprite->changeAnimation(STAND_LEFT);
			}

			//movent = false;
		//}

		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
		{
			if (sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);
			posPlayer.x += 2;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.x -= 2;
				sprite->changeAnimation(STAND_RIGHT);
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_UP))
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
			if (sprite->animation() == MOVE_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == MOVE_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
			else if (sprite->animation() == MOVE_UP)
				sprite->changeAnimation(STAND_UP);
			else if (sprite->animation() == MOVE_DOWN)
				sprite->changeAnimation(STAND_DOWN);
		}

		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	}
}

void Player::render()
{
	sprite->render();
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




