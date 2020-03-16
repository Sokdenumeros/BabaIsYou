#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	Player(string nam, bool isnam, float sx, float sy, int mapx, int mapy);
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime, int i, int j);
	void up(int deltaTime);
	void render();
	bool getmove();
	void setmove(bool b);
	void setpush(bool b);
	void setsink(bool b);
	int count = 0;
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	float getposx();
	float getposy();
	string getname();
	bool itsname();
	int getmapx();
	int getmapy();
	bool getpush();
	bool getsink();
	void setmapy(int j);
	
private:
	bool bJumping;
	bool movent = false;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	int sizex, sizey;
	vector<vector<int>> matriu;
	
	int tamany;
	float sprx, spry;
	Sprite* spr;
	string name;
	bool win, defeat, you;
	bool sink = false;
	bool push = false;
	bool isname;
	int posmapax, posmapay;
	bool move = false;

};


#endif // _PLAYER_INCLUDE


