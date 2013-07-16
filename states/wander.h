#pragma once
#include <SFML/Graphics.hpp>
#include "../gs.h"
#include "../res.h"
#include "mainmenu.h"
#include "luastuff.h"
#define luareg(X, Y, Z) lua_pushcfunction(X, Y);lua_setglobal(X, Z)

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
	void activateobject(MapObject * o);
	virtual ~WanderState(){}
	std::vector<MapObject *> objects;
	Map* map;
private:
	sf::Sprite* tiledrawer;
	std::string* mapscript;
	lua_State* lua;
};
