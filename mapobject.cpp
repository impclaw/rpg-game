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
	blocking = false;
	centered = false;
	walkover = false;
	frozen = false;
	this->engine = engine;
	speed = 2;
	if(spritename != "")
		sprite = new sf::Sprite(*(engine->resources->getTexture(spritename)));
	else
		sprite = NULL;
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

MapObject::~MapObject()
{
	std::cout << "MapObject Cleared" << std::endl;
}

void MapObject::update()
{
	if(walkstate == 1) // Walking
	{
		int step = speed > stepsleft ? stepsleft : speed;
		switch(direction)
		{
			case 1: y+=step; break;
			case 2: x-=step; break;
			case 3: x+=step; break;
			case 4: y-=step; break;
		}
		stepsleft-=step;
		if(stepsleft == 0)
			walkstate = 0;
	}
}

void MapObject::render(GameEngine * engine)
{
	if(sprite == NULL)
		return;

	int srcx = 1;
	int srcy = direction-1;
	if(walkstate == 1)
		srcx = stepsleft / 12;

	sprite->setTextureRect(sf::IntRect(srcx*32, srcy*32, 32, 32));

	if(centered)
		sprite->setPosition(engine->viewwidth/2-32, engine->viewheight/2-32);
	else
	{
		int px = engine->player->getx(); // player coords
		int py = engine->player->gety();
		int sx = -px + engine->viewwidth / 2 - 32; //player character location
		int sy = -py + engine->viewheight / 2 - 32;
		sprite->setPosition(sf::Vector2f(x+sx, y+sy));
	}
		engine->window->draw(*sprite);
}

void MapObject::setparent(WanderState * state)
{
	parent = state;
}

void MapObject::step(int dir)
{
	if(walkstate == 0 && !frozen)
	{
		WanderState* state = dynamic_cast<WanderState*>(engine->currentstate());
		Map * map = state->map;
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
		for(auto o : state->objects)
		{
			if(o->mapx == nextmapx && o->mapy == nextmapy && o->blocking)
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
}

void MapObject::face(MapObject * target)
{
	direction = 5 - target->direction;
}

int MapObject::getx() { return x; }
int MapObject::gety() { return y; }
int MapObject::getmapx() { return mapx; }
int MapObject::getmapy() { return mapy; }
int MapObject::getdirection() { return direction; }

void MapObject::setblocking(bool b) { blocking = b; }
void MapObject::setwalkover(bool b) { walkover = b; }
void MapObject::setfrozen(bool b) { frozen = b; }
void MapObject::setposition(int _x, int _y) 
{ 
	mapx = _x; 
	mapy = _y; 
	x = mapx * 32;
	y = mapy * 32;
}

void MapObject::lua_onactivate(luabridge::LuaRef ll) 
{
	onactivatef = new luabridge::LuaRef(ll);
}

void MapObject::onactivate()
{
	(*onactivatef)();
}
