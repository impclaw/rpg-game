#pragma once
#include <SFML/Graphics.hpp>
#include "../gs.h"
#include "../res.h"
#include "mainmenu.h"

class WanderState : public GameState
{
public:
	virtual void init(GameEngine*);
	virtual void cleanup();
	virtual void keypressed(GameEngine*, int key);
	virtual void pause();
	virtual void resume();
	virtual void update(GameEngine*);
	virtual void render(GameEngine*);
	virtual ~WanderState(){}
private:
	sf::Sprite* tiledrawer;
	Map* map;
};
