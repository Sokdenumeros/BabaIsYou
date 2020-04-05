#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	Player(Player* P, int x, int y);
	Player(string nam, bool isnam, float sx, float sy, int mapx, int mapy);
	void init(ShaderProgram &shaderProgram, Texture* ss);
	void update(int deltaTime, int i, int j);
	void update(int deltaTime);
	void up(int deltaTime);
	void render();
	void setPosition(const glm::vec2 &pos);
	float getposx();
	float getposy();
	string getname();
	bool itsname();
	bool getmove();
	void setmove(bool b);
	bool getpush();
	void setpush(bool b);
	void sethasname(string s);
	string gethasname();
	bool getsink();
	void setsink(bool b);
	bool getwin();
	void setwin(bool b);
	bool getdefeat();
	void setdefeat(bool b);
	int getPosPlayerx();
	int getPosPlayery();
	void static setoffx(int x);
	void static setoffy(int y);
	
private:
	static glm::ivec2 tileMapDispl;
	glm::ivec2 posPlayer;
	Texture *spritesheet;
	Sprite *sprite;
	int count;
	float sprx, spry;
	string name;
	bool win, defeat, move, sink, push;
	string hasname = "ningu";
	bool isname;

};


#endif // _PLAYER_INCLUDE


