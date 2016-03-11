#include "gs.h"
#include "player.h" // forward declarations

void GameEngine::init(sf::RenderWindow * wnd, int vw, int vh)
{
	resources = new Resources("data.pk3");
	player = new Player(this);
	db = new Database(this);
	window = wnd;
	sf::View view;
	viewwidth = vw;
	viewheight = vh;
	view.reset(sf::FloatRect(0, 0, vw, vh));
	double dh = (1.7777777777 - 1920/1200.0f)/2.0;
	view.setViewport(sf::FloatRect(0.f, dh, 1.f, 1.f-dh*2));
	window->setView(view);
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
