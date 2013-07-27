#pragma once
#include <SFML/Window.hpp>
#include "../gs.h"

class XButton
{
public:
	XButton(GameEngine*, std::string, int, int, int, int);
	void update();
	void render(GameEngine*);
	void activate();
	void deactivate();
	void settext(std::string);
private:
	int x, y, w, h; 
	bool active;
	sf::RectangleShape * bg;
	sf::Text * txt;
};
