#include "xbutton.h"
#include "../states/mainmenu.h"

XButton::XButton(GameEngine * engine, std::string text, int _x, int _y, int _w, int _h)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	active = false;

	bg = new sf::RectangleShape();
	bg->setPosition(x, y);
	bg->setSize(sf::Vector2f(w, h));
	bg->setOutlineThickness(0);
	bg->setFillColor(MainMenuState::fillcolor);
	bg->setOutlineColor(MainMenuState::outlinecolor);


	txt = new sf::Text(text, engine->resources->mainfont, 26U);
	txt->setPosition(x+6, y-8);
}

void XButton::activate()
{
	bg->setOutlineThickness(2);
	bg->setFillColor(MainMenuState::lightfillcolor);
	active = true;
}

void XButton::deactivate()
{

	bg->setOutlineThickness(0);
	bg->setFillColor(MainMenuState::fillcolor);
	active = true;
}

void XButton::settext(std::string s)
{
	txt->setString(s);
}

void XButton::update()
{

}

void XButton::render(GameEngine* engine)
{
	engine->window->draw(*bg);
	engine->window->draw(*txt);
}
