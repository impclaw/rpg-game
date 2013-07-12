#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "res.h"
#include "gs.h"

class MapObject
{
public:
	MapObject(GameEngine *, std::string);
	void update();
	void render(GameEngine *);
	void step(int dir);
	void setmap(Map *);
	int x, y;
	int mapx, mapy;
	int direction; // 1^, 2<-, 3->, 4v
private:
	Map * map;
	sf::Sprite* sprite;
	int walkstate;
	int stepsleft;
};

