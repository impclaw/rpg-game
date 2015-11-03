#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "res.h"
#include "gs.h"

extern "C"
{
    #include <lua5.1/lua.h>
    #include <lua5.1/lauxlib.h>
    #include <lua5.1/lualib.h>
}
#include "lb/LuaBridge.h"
extern lua_State *lua_main;

class WanderState;

class MapObject
{
public:
	void _init(GameEngine *, std::string);
	MapObject(GameEngine *, std::string);
	MapObject(GameEngine *, std::string, std::string, int, int);
	void update();
	void render(GameEngine *);
	void step(int dir);
	void turn(int dir);
	void face(MapObject * target);
	void setparent(WanderState *);
	bool centered; //specific for the player
	std::string name;
	int x, y;
	bool blocking, walkover, frozen;
	int mapx, mapy;
	int direction; // 1^, 2<-, 3->, 4v
	WanderState * parent; // Used for things like collisions

	// Accessors
	int getx();
	int gety();
	int getmapx();
	int getmapy();
	int getdirection();

	// Mutators
	void setblocking(bool b);
	void setwalkover(bool b);
	void setfrozen(bool b);
	void setposition(int _x, int _y);

	// Callback Functions
	luabridge::LuaRef * onactivatef;
	void lua_onactivate(luabridge::LuaRef ll); 
	void onactivate();

private:
	sf::Sprite* sprite;
	int walkstate;
	int stepsleft;
};

