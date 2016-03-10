#include "message.h"

MessageState::MessageState(GameEngine* engine, std::string ttl, std::string msg) 
{
	MessageState(engine, ttl, msg, 1);
}

MessageState::MessageState(GameEngine* engine, std::string ttl, std::string msg, int pos) 
{
	MessageState(engine, ttl, msg, pos, "");
}

MessageState::MessageState(GameEngine* engine, std::string ttl, std::string msg, int pos, std::string facesprite)
{
	fadedir = 0;
	fadevalue = 0;
	title = ttl;
	fullmessage = msg;
	message = "";
	position = pos;
	drawnletters = lettertimer = 0;
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

	if(!facesprite.empty()) {
		sprite = new sf::Sprite(*(engine->resources->getTexture(facesprite)));
		spritebg = new sf::RectangleShape();
		sprite->setPosition(64, y+32);
		bodytxt->setPosition(190, y+12);
		spritebg->setSize(sf::Vector2f(100, 100));
		spritebg->setPosition(64, y+32);
		spritebg->setOutlineThickness(2);
		spritebg->setFillColor(MainMenuState::fillcolor);
		spritebg->setOutlineColor(MainMenuState::outlinecolor);
	}
	else {
		sprite = NULL;
		spritebg = NULL;
	}

}

MessageState::~MessageState()
{
	delete bodytxt;
	delete titletxt;
	delete titlebg;
	delete bg;
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
	lettertimer++;
	if (lettertimer > 2 && (unsigned long)drawnletters < fullmessage.length())
	{
		message += fullmessage[drawnletters];
		bodytxt->setString(message);
		drawnletters++;
		lettertimer = 0;
	}
	if(fadedir == -1 && (unsigned long)drawnletters == fullmessage.length())
	{
		engine->popstate();
		onclose();
	}
}

void MessageState::render(GameEngine* engine)
{
	engine->window->draw(*bg);
	engine->window->draw(*bodytxt);
	engine->window->draw(*titlebg);
	engine->window->draw(*titletxt);
	if(spritebg != NULL)
		engine->window->draw(*spritebg);
	if(sprite != NULL)
		engine->window->draw(*sprite);
}

void MessageState::lua_onclose(luabridge::LuaRef ll) 
{
	onclosef = new luabridge::LuaRef(ll);
}

void MessageState::onclose()
{
	if(onclosef != NULL) (*onclosef)();
}
