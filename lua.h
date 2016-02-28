extern "C"
{
    #include <lua5.1/lua.h>
    #include <lua5.1/lauxlib.h>
    #include <lua5.1/lualib.h>
}
#include "lb/LuaBridge.h"
#include "states/wander.h"
#include "states/message.h"
#include "gs.h"
#include "res.h"

extern lua_State * lua;
extern GameEngine * lua_game;

void lua_pushstate (WanderState * test);
GameEngine * lua_grabengine();
void luareg();
void luaclose();
void runluafile(std::string s);
