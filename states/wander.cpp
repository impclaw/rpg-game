#include "wander.h"

void WanderState::init(GameEngine* engine)
{
	tiledrawer = new sf::Sprite(*(engine->resources->getTexture("tiles")));
	map = engine->resources->getMap("entry");
}

void WanderState::cleanup()
{
}

void WanderState::keypressed(GameEngine* engine, int key)
{
	if(key == sf::Keyboard::Escape)
	{
		MainMenuState* mm = new MainMenuState();
		mm->init(engine);
		engine->pushstate(mm);
	}
	engine->player->keydown(key);
}

void WanderState::pause()
{
}

void WanderState::resume()
{
}

void WanderState::update(GameEngine* engine)
{
	engine->player->update();
}

void WanderState::render(GameEngine* engine)
{
	int px = engine->player->x; // player coords
	int py = engine->player->y;
	int sx = px + 800 / 2 - 32; //screen coords
	int sy = py + 600 / 2 - 32;
	for(int n = 0; n < map->width * map->height; n++)
	{
		int tilen = map->tiles[n].index;
		tiledrawer->setTextureRect(sf::IntRect((tilen%32)*32, (tilen/32)*32, 32, 32));
		tiledrawer->setPosition(sf::Vector2f(n%map->width*32+sx, n/map->height*32+sy));
		engine->window->draw(*tiledrawer);
	}
}

