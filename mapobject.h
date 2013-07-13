#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "res.h"
#include "gs.h"

class MapObject
{
public:
	void _init(GameEngine *, std::string);
	MapObject(GameEngine *, std::string);
	MapObject(GameEngine *, std::string, std::string, int, int);
	void update();
	void render(GameEngine *);
	void step(int dir);
	void setmap(Map *);
	bool centered; //specific for the player
	std::string name;
	int x, y;
	int mapx, mapy;
	int direction; // 1^, 2<-, 3->, 4v
private:
	Map * map;
	sf::Sprite* sprite;
	int walkstate;
	int stepsleft;
};

