#include "lua.h"

using namespace luabridge;
lua_State * lua = 0;
GameEngine * lua_game = 0;

void lua_pushstate (WanderState * test)
{ 
	test->init(lua_game);
	lua_game->pushstate(test);
	printf("Test WORKING\n"); 
}

GameEngine * lua_grabengine()
{
	return lua_game;
}

void luareg()
{
	lua = luaL_newstate();
	luaL_openlibs(lua);
	
	getGlobalNamespace(lua)
		.beginClass<WanderState>("CWanderState")
			.addConstructor <void (*) (void)> ()
			.addFunction ("add", &WanderState::addobject)
		.endClass();

	getGlobalNamespace(lua)
		.beginClass<GameEngine>("CGameEngine")
			.addConstructor <void (*) (void)> ()
		.endClass();

	getGlobalNamespace(lua)
		.beginClass<MapObject>("CEvent")
			.addConstructor <void (*) (GameEngine*,std::string,std::string,int,int)> ()
			.addFunction("onActivate", &MapObject::lua_onactivate)
			.addFunction("turn", &MapObject::turn)
		.endClass();

	/*getGlobalNamespace(lua)
		.beginClass<GameState>("CGameState")
			.addConstructor <void (*) (void)> ()
		.endClass()
		.deriveClass<WanderState, GameState>("CWanderState")
			.addConstructor <void (*) (void)> ()
		.endClass();*/

	getGlobalNamespace(lua)
		.addFunction("PushState", lua_pushstate)
		.addFunction("GrabEngine", lua_grabengine);
}

