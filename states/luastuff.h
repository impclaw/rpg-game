#pragma once
extern "C" {
	#include <lua5.1/lua.h>
	#include <lua5.1/lualib.h>
	#include <lua5.1/lauxlib.h>
}
class WanderState;
class GameEngine;
class MapObject;
class MessageState;

extern WanderState *lua_wanderstate;
extern GameEngine *lua_game_engine;

int lua_place_event(lua_State *L);
int lua_message(lua_State *L);
