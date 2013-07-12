#include "mapobject.h"

MapObject::MapObject(GameEngine * engine, std::string spritename)
{
	x = y = 0;
	mapx = mapy = 0;
	stepsleft = 0;
	walkstate = 0;
	direction = 1;
	map = NULL;
	sprite = new sf::Sprite(*(engine->resources->getTexture(spritename)));
	sprite->setPosition(800/2-32, 600/2-32);
	update();
}

void MapObject::update()
{
	if(walkstate == 1) // Walking
	{
		switch(direction)
		{
			case 1: y+=2; break;
			case 2: x-=2; break;
			case 3: x+=2; break;
			case 4: y-=2; break;
		}
		stepsleft-=2;
		if(stepsleft == 0)
			walkstate = 0;
	}
	int srcx = 1;
	int srcy = direction-1;
	if(walkstate == 1)
		srcx = stepsleft / 12;
	sprite->setTextureRect(sf::IntRect(srcx*32, srcy*32, 32, 32));
}

void MapObject::render(GameEngine * engine)
{
	engine->window->draw(*sprite);
}

void MapObject::setmap(Map * newmap)
{
	map = newmap;
}

void MapObject::step(int dir)
{
	if(walkstate == 0)
	{
		int nextmapx = mapx;
		int nextmapy = mapy;
		switch(dir)
		{
			case 1: nextmapy++; break;
			case 2: nextmapx--; break;
			case 3: nextmapx++; break;
			case 4: nextmapy--; break;
		}
		//printf("mX: %d mY: %d :: ", mapx, mapy);
		//printf("nmX: %d nmY: %d\n", nextmapx, nextmapy);
		int mapcoord = nextmapy * map->width + nextmapx;
		if(mapcoord < 0 || mapcoord > map->width * map->height);
		else if(nextmapx >= map->width || nextmapy >= map->height);
		else if(nextmapx < 0 || nextmapy < 0);
		else if(map->layer[0][mapcoord].blocking);
		else
		{
			walkstate = 1;
			stepsleft = 32;
			mapx = nextmapx;
			mapy = nextmapy;
		}
		direction = dir;
	}
}

