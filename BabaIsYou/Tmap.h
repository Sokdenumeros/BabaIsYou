#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.

enum Direction { UP, DOWN, LEFT, RIGHT };

class Tmap
{

public:
	// Tile maps can only be created inside an OpenGL context

	Tmap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);
	~Tmap();

	void render() const;
	void free();

	int getTileSize() const { return tileSize; }

	bool Move(const glm::ivec2 &pos, const glm::ivec2 &size, const Direction& d) const;

private:
	bool loadLevel(const string &levelFile);
	void prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program);

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;



	int *map;

};


#endif // _TILE_MAP_INCLUDE


