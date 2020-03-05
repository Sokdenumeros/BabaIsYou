#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Tmap.h"


using namespace std;

Tmap::Tmap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
}

Tmap::~Tmap()
{
	if (map != NULL) delete map;
}

void Tmap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool Tmap::Move(const glm::ivec2 &pos, const glm::ivec2 &size, const Direction& d) const
{
	switch (d) {
	case UP:
		int x, y0, y1;

		x = pos.x / tileSize;
		y0 = pos.y / tileSize;
		y1 = (pos.y + size.y - 1) / tileSize;
		for (int y = y0; y <= y1; y++)
		{
			if (map[y*mapSize.x + x] != 0)
				return true;
		}
		return false;
	case DOWN:
		int x, y0, y1;

		x = pos.x / tileSize;
		y0 = pos.y / tileSize;
		y1 = (pos.y + size.y - 1) / tileSize;
		for (int y = y0; y <= y1; y++)
		{
			if (map[y*mapSize.x + x] != 0)
				return true;
		}
		return false;
	case RIGHT:
		int x, y0, y1;

		x = pos.x / tileSize;
		y0 = pos.y / tileSize;
		y1 = (pos.y + size.y - 1) / tileSize;
		for (int y = y0; y <= y1; y++)
		{
			if (map[y*mapSize.x + x] != 0)
				return true;
		}
		return false;
	case LEFT:
		int x, y0, y1;

		x = pos.x / tileSize;
		y0 = pos.y / tileSize;
		y1 = (pos.y + size.y - 1) / tileSize;
		for (int y = y0; y <= y1; y++)
		{
			if (map[y*mapSize.x + x] != 0)
				return true;
		}
		return false;
	}
	
}

void Tmap::prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program)
{
	int tile, nTiles = 0;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;

	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height()); //mitja textura petita
	for (int j = 0; j<mapSize.y; j++)
	{
		for (int i = 0; i<mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];
			if (tile != 0)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				texCoordTile[0] = glm::vec2(float((tile - 1) % 32) / tilesheetSize.x, float((tile - 1) / 32) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				//texCoordTile[0] += halfTexel;
				texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);							//vertex a block block
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);			//textures del vertex
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);				//vertex a x+block y+block
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);			//textures del vertex
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//24 * nTiles perque tenim 2 triangles de 3 vertex i 4 floats per cadascun: un vec2 de coordenades de textures i un vec2 de posicio
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void *)(2 * sizeof(float)));
}

void Tmap::render() const
{
	//prepareArrays
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * mapSize.x * mapSize.y);
	glDisable(GL_TEXTURE_2D);
}