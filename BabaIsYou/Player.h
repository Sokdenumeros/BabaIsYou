#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	Player(string nam, bool isnam, float sx, float sy, int mapx, int mapy);
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, Texture* ss);
	void update(int deltaTime, int i, int j);
	void up(int deltaTime);
	void render();
	int count = 0;
	void setPosition(const glm::vec2 &pos);
	float getposx();
	float getposy();
	string getname();
	bool itsname();
	int getmapx();
	int getmapy();
	bool getmove();
	void setmove(bool b);
	bool getpush();
	string getsomeone();
	void setpush(bool b);
	bool getsink();
	void setsink(bool b);
	bool getwin();
	void setwin(bool b);
	bool getdefeat();
	void setdefeat(bool b);
	void setmapy(int j);
	void setmapax(int i);
	void setsomeone(string s);
	
private:
	bool bJumping;
	bool movent = false;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture *spritesheet;
	Sprite *sprite;
	int sizex, sizey;
	
	int tamany;
	float sprx, spry;
	string name;
	bool win, defeat, you, sink, push;
	string someone = "ningu";
	bool isname;
	int posmapax, posmapay;
	bool move = false;

};


#endif // _PLAYER_INCLUDE


