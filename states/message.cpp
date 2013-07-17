#include "message.h"

void MessageState::init(GameEngine* engine)
{
	init(engine, "", "", 1);
}

void MessageState::init(GameEngine* engine, std::string ttl, std::string msg, int pos)
{
	fadedir = 0;
	fadevalue = 0;
	title = ttl;
	message = msg;
	position = pos;
	bg = new sf::RectangleShape();
	bg->setSize(sf::Vector2f(800-100, 600/4));
	int y;
	switch(pos)
	{
		case 1: y = 32; break;
		case 2: y = 225; break;
		case 3: y = 350; break;
	}
	bg->setPosition(50, y);
	bg->setOutlineThickness(2);
	bg->setFillColor(MainMenuState::fillcolor);
	bg->setOutlineColor(MainMenuState::outlinecolor);

	titlebg = new sf::RectangleShape();
	titlebg->setSize(sf::Vector2f(160, 28));
	titlebg->setPosition(62, y-14);
	titlebg->setOutlineThickness(2);
	titlebg->setFillColor(MainMenuState::fillcolor);
	titlebg->setOutlineColor(MainMenuState::outlinecolor);

	titletxt = new sf::Text(title, engine->resources->mainfont, 28U);
	titletxt->setPosition(70, y-20);

	bodytxt = new sf::Text(message, engine->resources->mainfont, 28U);
	bodytxt->setPosition(58, y+12);

}

void MessageState::cleanup()
{
	delete bodytxt;
	delete titletxt;
	delete titlebg;
	delete bg;
	onclose();
}

void MessageState::keypressed(GameEngine*, int key)
{
	if(key == sf::Keyboard::Return)
		fadedir = -1;
}

void MessageState::pause()
{
}

void MessageState::resume()
{
}

void MessageState::update(GameEngine* engine)
{
	if(fadedir == -1)
		engine->popstate();
}

void MessageState::render(GameEngine* engine)
{
	engine->window->draw(*bg);
	engine->window->draw(*bodytxt);
	engine->window->draw(*titlebg);
	engine->window->draw(*titletxt);
}

void MessageState::lua_onclose(luabridge::LuaRef ll) 
{
	onclosef = new luabridge::LuaRef(ll);
}

void MessageState::onclose()
{
	(*onclosef)();
}
