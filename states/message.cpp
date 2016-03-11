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
	bg->setSize(sf::Vector2f(engine->viewwidth-32, engine->viewheight/4));
	int y;
	switch(pos)
	{
		case 1: y = 16; break;
		case 2: y = 225; break;
		case 3: y = 350; break;
	}
	bg->setPosition(16, y);
	bg->setOutlineThickness(2);
	bg->setFillColor(MainMenuState::fillcolor);
	bg->setOutlineColor(MainMenuState::outlinecolor);

	titlebg = new sf::RectangleShape();
	titlebg->setSize(sf::Vector2f(120, 20));
	titlebg->setPosition(32, y-10);
	titlebg->setOutlineThickness(1);
	titlebg->setFillColor(MainMenuState::fillcolor);
	titlebg->setOutlineColor(MainMenuState::outlinecolor);

	titletxt = new sf::Text(title, engine->resources->mainfont, 14U);
	titletxt->setPosition(40, y-10);

	bodytxt = new sf::Text(message, engine->resources->mainfont, 14U);
	bodytxt->setPosition(40, y+12);

	if(!facesprite.empty()) {
		sprite = new sf::Sprite(*(engine->resources->getTexture(facesprite)));
		spritebg = new sf::RectangleShape();
		sprite->setPosition(32, y+13);
		sprite->setScale(0.75f, 0.75f);
		bodytxt->setPosition(32+75+16, y+12);
		spritebg->setSize(sf::Vector2f(75, 75));
		spritebg->setPosition(32, y+13);
		spritebg->setOutlineThickness(1);
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
	if (sprite != NULL) delete sprite;
	if (spritebg != NULL) delete spritebg;
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
