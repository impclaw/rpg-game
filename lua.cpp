#include "lua.h"

using namespace luabridge;
lua_State * lua = 0;
GameEngine * lua_game = 0;

void lua_pushstate (GameState * t)
{ 
	lua_game->pushstate(t);
}
void lua_pushwander (WanderState * t) { lua_game->pushstate(t); }
void lua_pushmessage (MessageState * t) { lua_game->pushstate(t); }

GameEngine * lua_grabengine()
{
	return lua_game;
}

void luareg()
{
	lua = luaL_newstate();
	luaL_openlibs(lua);
	
	getGlobalNamespace(lua)
		.beginClass<GameState>("CGameState")
		.endClass()
		.deriveClass<MessageState, GameState>("CMessageState")
			.addConstructor <void (*) (GameEngine*, std::string, std::string, int)> ()
			.addFunction ("onClose", &MessageState::lua_onclose)
		.endClass()
		.deriveClass<WanderState, GameState>("CWanderState")
			.addConstructor <void (*) (GameEngine*)> ()
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
		//.addFunction("PushState", lua_pushstate)
		.addFunction("PushWander", lua_pushwander)
		.addFunction("PushMessage", lua_pushmessage)
		.addFunction("GrabEngine", lua_grabengine);
}

