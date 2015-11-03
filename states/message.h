#pragma once
#include <SFML/Graphics.hpp>
#include "../gs.h"
#include "../res.h"
#include "mainmenu.h"

extern "C"
{
    #include <lua5.1/lua.h>
    #include <lua5.1/lauxlib.h>
    #include <lua5.1/lualib.h>
}
#include "../lb/LuaBridge.h"

class MessageState : public GameState
{
public:
	MessageState(GameEngine*, std::string, std::string, int);
	virtual void keypressed(GameEngine*, int key);
	virtual void pause();
	virtual void resume();
	virtual void update(GameEngine*);
	virtual void render(GameEngine*);

	// Callback Functions
	luabridge::LuaRef * onclosef = NULL;
	void lua_onclose(luabridge::LuaRef ll); 
	void onclose();

	virtual ~MessageState();
private:
	int position;
	int fadedir;
	int fadevalue;

	std::string message;
	std::string title;

	sf::RectangleShape* bg;
	sf::RectangleShape* bgblur;
	sf::RectangleShape* fade;
	sf::RectangleShape* titlebg;

	sf::Text* titletxt;
	sf::Text* bodytxt;
};
