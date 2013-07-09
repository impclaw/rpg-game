#pragma once
#include <SFML/Graphics.hpp>
#include "../gs.h"
#include "../res.h"
#include "mainmenu.h"

class MessageState : public GameState
{
public:
	virtual void init(GameEngine*);
	virtual void init(GameEngine*, std::string, std::string, int);
	virtual void cleanup();
	virtual void keypressed(GameEngine*, int key);
	virtual void pause();
	virtual void resume();
	virtual void update(GameEngine*);
	virtual void render(GameEngine*);
	virtual ~MessageState(){}
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
