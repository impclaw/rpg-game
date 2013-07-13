#include "wander.h"

WanderState *lua_wanderstate;
GameEngine *lua_game_engine;

static int lua_place_event(lua_State *L)
{
	const char * name = lua_tostring(L, 1);
	const char * sprite = lua_tostring(L, 2);
	int xpos = lua_tonumber(L, 3);
	int ypos = lua_tonumber(L, 4);
	printf("%s %s\n", name, sprite);
	MapObject *obj = new MapObject(lua_game_engine, sprite, name, xpos, ypos);
	lua_wanderstate->objects.push_back(obj);
	return 0;
}

void WanderState::init(GameEngine* engine)
{
	tiledrawer = new sf::Sprite(*(engine->resources->getTexture("tiles")));
	map = engine->resources->getMap("entry.map");
	mapscript = engine->resources->getText("entry.lua");
	lua = luaL_newstate();
	luaL_openlibs(lua);
	lua_wanderstate = this;
	lua_game_engine = engine;
	lua_pushcfunction(lua, lua_place_event);
	lua_setglobal(lua, "place_event");
	luaL_dostring(lua, mapscript->c_str());
	//char * lua="a=1+1;\n";
	//lua_dostring(luavm, lua);
	//Register all functions here
	
	engine->player->setmap(map);
}

void WanderState::cleanup()
{
	lua_close(lua);
}

void WanderState::keypressed(GameEngine* engine, int key)
{
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
	engine->player->update();
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

