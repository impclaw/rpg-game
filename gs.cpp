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
	info("Pushing Gamestate");
	states.push_back(gs);
}
void GameEngine::popstate()
{
	info("Popping Gamestate");
	if(states.size() > 0)
	{
		GameState * gs = states.back();
		//delete gs; //TODO: Are we managed by lua?
		states.pop_back();
	}
	else
		info("Can't Pop Gamestate, No State To Pop! ");
}
