#pragma once
extern "C" {
	#include <lua5.1/lua.h>
	#include <lua5.1/lualib.h>
	#include <lua5.1/lauxlib.h>
}
#include <SFML/Graphics.hpp>
#include "../gs.h"
#include "../res.h"
#include "mainmenu.h"

class WanderState : public GameState
{
public:
	virtual void init(GameEngine*);
	virtual void cleanup();
	virtual void keypressed(GameEngine*, int key);
	virtual void pause();
	virtual void resume();
	virtual void update(GameEngine*);
	virtual void render(GameEngine*);
	virtual ~WanderState(){}
	std::vector<MapObject *> objects;
private:
	sf::Sprite* tiledrawer;
	std::string* mapscript;
	lua_State* lua;
	Map* map;
};
