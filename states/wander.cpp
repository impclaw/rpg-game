#include "wander.h"

WanderState::WanderState(GameEngine* engine)
{
	tiledrawer = new sf::Sprite(*(engine->resources->getTexture("tiles.png")));
	map = engine->resources->getMap("entry.map");
	engine->player->setparent(this);
}

WanderState::~WanderState()
{
}

void WanderState::addobject(MapObject * o)
{
	if(o == NULL)
	{
		fprintf(stderr, "ERROR: Attempting to att nil event to wanderstate. ");
		exit(0);
	}
	objects.push_back(o);
}

void WanderState::wait(int ticks)
{
	waitticks = ticks;
}

void WanderState::activateobject(MapObject * o)
{
	/*switch(lua_game_engine->player->obj->direction)
	{
		case 1: o->turn(4); break;
		case 2: o->turn(3); break;
		case 3: o->turn(2); break;
		case 4: o->turn(1); break;
	}
	o->update();*/
	o->onactivate();
}

void WanderState::keypressed(GameEngine* engine, int key)
{
	if(waitticks > 0)
		return;
	if(key == sf::Keyboard::Escape)
	{
		MainMenuState* mm = new MainMenuState();
		mm->init(engine);
		engine->pushstate(mm);
	}
	engine->player->keydown(key);
}

void WanderState::pause()
{
}

void WanderState::resume()
{
}

void WanderState::update(GameEngine* engine)
{
	if(waitticks > 0)
		waitticks--;
	else if (waitticks == 0)
	{
		waitticks = -1;
		onwaitdone();
	}
	engine->player->update();
	for(auto o : objects)
		o->update();
}

void WanderState::render(GameEngine* engine)
{
	int px = engine->player->getx(); // player coords
	int py = engine->player->gety();
	int sx = -px + 800 / 2 - 32; //player character location
	int sy = -py + 600 / 2 - 32;
	for(int n = 0; n < map->width * map->height; n++)
	{
		for(int l = 0; l < 3; l++)
		{
			int tilen = map->layer[l][n].index;
			if(tilen == 0) 
				continue; //Don't draw invisible tiles
			tiledrawer->setTextureRect(sf::IntRect((tilen%32)*32, (tilen/32)*32, 32, 32));
			tiledrawer->setPosition(sf::Vector2f(n%map->width*32+sx, n/map->width*32+sy));
			engine->window->draw(*tiledrawer);
		}
	}
	for(auto obj : objects)
	{
		obj->render(engine);
	}
	engine->player->render(engine);
}

void WanderState::lua_onwaitdone(luabridge::LuaRef ll) 
{
	onwaitdonef = new luabridge::LuaRef(ll);
}

void WanderState::onwaitdone()
{
	if(onwaitdonef != NULL) (*onwaitdonef)();
}
