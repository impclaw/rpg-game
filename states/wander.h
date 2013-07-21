#pragma once
#include <SFML/Graphics.hpp>
#include "../gs.h"
#include "../res.h"
#include "mainmenu.h"

class WanderState : public GameState
{
public:
	WanderState(GameEngine*);
	virtual void keypressed(GameEngine*, int key);
	virtual void pause();
	virtual void resume();
	virtual void update(GameEngine*);
	virtual void render(GameEngine*);
	void activateobject(MapObject * o);
	void addobject(MapObject*);
	void wait(int ticks);

	virtual ~WanderState();
	std::vector<MapObject *> objects;
	Map* map;

	//Callback Functions
	luabridge::LuaRef * onwaitdonef = NULL;
	void lua_onwaitdone(luabridge::LuaRef ll); 
	void onwaitdone();
private:
	sf::Sprite* tiledrawer;
	int waitticks = -1;
};
