#include "mapobject.h"
#include "player.h"
#include "states/wander.h"

void MapObject::_init(GameEngine * engine, std::string spritename)
{
	x = y = 0;
	mapx = mapy = 0;
	stepsleft = 0;
	walkstate = 0;
	direction = 1;
	centered = false;
	map = NULL;
	sprite = new sf::Sprite(*(engine->resources->getTexture(spritename)));
}

MapObject::MapObject(GameEngine * engine, std::string spritename)
{
	_init(engine, spritename);
	update();
}

MapObject::MapObject(GameEngine * engine, std::string oname, std::string spritename, int mx, int my)
{
	_init(engine, spritename);
	mapx = mx;
	mapy = my;
	x = mapx * 32;
	y = mapy * 32;
	name = oname;
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
	if(centered)
		sprite->setPosition(800/2-32, 600/2-32);
	else
	{
		int px = engine->player->getx(); // player coords
		int py = engine->player->gety();
		int sx = -px + 800 / 2 - 32; //player character location
		int sy = -py + 600 / 2 - 32;
		sprite->setPosition(sf::Vector2f(x+sx, y+sy));
	}
	engine->window->draw(*sprite);
}

void MapObject::setparent(WanderState * state)
{
	parent = state;
	map = parent->map;
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
		
		bool ocol = false;
		for(auto o : parent->objects)
		{
			if(o->mapx == nextmapx && o->mapy == nextmapy)
				ocol = true;
		}
		
		int mapcoord = nextmapy * map->width + nextmapx;
		if (ocol);
		else if(mapcoord < 0 || mapcoord > map->width * map->height);
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

void MapObject::turn(int dir)
{
	direction = dir;
	update();
}

void MapObject::face(MapObject * target)
{
	direction = 5 - target->direction;
	update();
}

int MapObject::getx() { return x; }
int MapObject::gety() { return y; }
int MapObject::getmapx() { return mapx; }
int MapObject::getmapy() { return mapy; }
int MapObject::getdirection() { return direction; }

void MapObject::lua_onactivate(luabridge::LuaRef ll) 
{
	onactivatef = new luabridge::LuaRef(ll);
}

void MapObject::onactivate()
{
	(*onactivatef)();
}
