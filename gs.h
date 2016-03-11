#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "res.h"
#include "db.h"

class Player;
class GameState;

class GameEngine
{
public:
	sf::RenderWindow *window;
	Resources *resources;
	Player *player;
	Database * db;

	void init(sf::RenderWindow*, int vw, int vh);
	void cleanup();
	void keypressed(int key);
	void update();
	void render();

	void pushstate(GameState*);
	void popstate();
	GameState* currentstate();
	int viewheight, viewwidth;
	int wndheight, wndwidth;
	int padtop;
	float scalex, scaley;

private:
	std::vector<GameState*> states;
};

class GameState
{
public:
	//virtual void init(GameEngine*) = 0;
	//virtual void cleanup() = 0;
	virtual void pause() = 0;
	virtual void resume() = 0;
	virtual void keypressed(GameEngine*, int key) = 0;
	virtual void update(GameEngine*) = 0;
	virtual void render(GameEngine*) = 0;
	virtual ~GameState() {};
	bool islua = false;
};

