#include "luastuff.h"

#include "wander.h"
#include "message.h"
#include "../gs.h"
#include "../mapobject.h"

WanderState *lua_wanderstate = 0;
GameEngine *lua_game_engine = 0;

int lua_place_event(lua_State *L)
{
	const char * name = lua_tostring(L, 1);
	const char * sprite = lua_tostring(L, 2);
	int xpos = lua_tonumber(L, 3);
	int ypos = lua_tonumber(L, 4);
	int dir = lua_tonumber(L, 5);
	MapObject *obj = new MapObject(lua_game_engine, sprite, name, xpos, ypos);
	obj->turn(dir);
	obj->setparent(lua_wanderstate);
	lua_wanderstate->objects.push_back(obj);
	return 0;
}

int lua_message(lua_State *L)
{
	const char * title = lua_tostring(L, 1);
	const char * message = lua_tostring(L, 2);
	MessageState * ms = new MessageState();
	ms->init(lua_game_engine, title, message, 1);
	lua_game_engine->pushstate(ms);
	return 0;
}
