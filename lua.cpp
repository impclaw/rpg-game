#include "lua.h"

using namespace luabridge;
lua_State * lua = 0;
GameEngine * lua_game = 0;

void lua_pushstate (GameState * t)
{ 
	t->islua = true;
	lua_game->pushstate(t);
}
void lua_pushwander (WanderState * t)    { t->islua = true; lua_game->pushstate(t); }
void lua_pushmessage (MessageState * t)  { t->islua = true; lua_game->pushstate(t); }
GameEngine * lua_grabengine() { return lua_game; }
Player * lua_grabplayer() { return lua_game->player; }

void lua_luaload(std::string s) {}

void runluafile(std::string filename)
{
	fprintf(stderr, "Loading Script: %s \n", filename.c_str());
	std::string* luascript = lua_game->resources->getText(filename);

	int pos = luascript->find("LuaLoad");
	if(pos != (int)std::string::npos)
	{
		pos += 9;
		const char * ll = luascript->c_str();
		char lfile[64]; //TODO: This is not secure!!!
		int i = 0;
		while(ll[pos] != '"')
			lfile[i++] = ll[pos++];
		lfile[i] = 0;
		runluafile(std::string(lfile));
	}

	if(luaL_dostring(lua, luascript->c_str()) == 1)
	{
		fprintf(stderr, "  Lua Error: %s\n", lua_tostring(lua, -1));
		exit(0);
	}
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
			.addFunction ("wait", &WanderState::wait)
			.addFunction ("onWaitDone", &WanderState::lua_onwaitdone)
		.endClass();

	getGlobalNamespace(lua)
		.beginClass<GameEngine>("CGameEngine")
			.addConstructor <void (*) (void)> ()
		.endClass();

	getGlobalNamespace(lua)
		.beginClass<MapObject>("CEvent")
			.addConstructor <void (*) (GameEngine*,std::string,std::string,int,int)> ()
			.addFunction("turn", &MapObject::turn)
			.addFunction("face", &MapObject::face)
			.addFunction("setBlocking", &MapObject::setblocking)
			.addFunction("onActivate", &MapObject::lua_onactivate)
		.endClass()
		.deriveClass<Player, MapObject>("CPlayer")
			.addFunction("getX", &Player::getmapx)
			.addFunction("getY", &Player::getmapy)
			.addFunction("getDirection", &Player::getdirection)
		.endClass();

	getGlobalNamespace(lua)
		//.addFunction("PushState", lua_pushstate)
		.addFunction("PushWander", lua_pushwander)
		.addFunction("PushMessage", lua_pushmessage)
		.addFunction("GrabPlayer", lua_grabplayer)
		.addFunction("GrabEngine", lua_grabengine)
		.addFunction("LuaLoad", lua_luaload);
}

void luaclose()
{
	lua_close(lua);
}
