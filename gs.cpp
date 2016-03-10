#include "gs.h"
#include "player.h" // forward declarations

void GameEngine::init(sf::RenderWindow * wnd)
{
	resources = new Resources("data.pk3");
	player = new Player(this);
	db = new Database(this);
	window = wnd;
}
void GameEngine::cleanup()
{
	delete resources;
	delete player;
	delete db;
}

void GameEngine::keypressed(int key)
{
	if(states.size() > 0)
		states.back()->keypressed(this, key);
}
void GameEngine::update()
{
	if(states.size() > 0)
		states.back()->update(this);
}
void GameEngine::render()
{
	for(auto s : states)
		s->render(this);
}
void GameEngine::pushstate(GameState* gs)
{
	states.push_back(gs);
}
GameState* GameEngine::currentstate()
{
	return states.back();
}
void GameEngine::popstate()
{
	if(states.size() > 0)
	{
		GameState * gs = states.back();
		if(!gs->islua)
			delete gs; 
		states.pop_back();
	}
	else
		info("Can't Pop Gamestate, No State To Pop! ");
}
