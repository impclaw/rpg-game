#include <SFML/Graphics.hpp>
#include "states/wander.h"
#include "gs.h"
#include "res.h"
#include "lua.h"

int main()
{
	GameEngine game;
	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);

	const int VIEW_HEIGHT = 360;
	const int VIEW_WIDTH = 640;
	const int WINDOW_WIDTH = 1680;
	const int WINDOW_HEIGHT = 1050;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Test Game");
	window.setKeyRepeatEnabled(true);
	window.setFramerateLimit(0);
	game.init(&window, 640, 360);
	lua_game = &game;
	luareg();
	runluafile("main.lua");
	while (window.isOpen())
	{
		sf::Event e;
		while(window.pollEvent(e))
		{
			if(e.type == sf::Event::Closed)
				window.close();
			if (e.type == sf::Event::KeyPressed)
				game.keypressed(e.key.code);
		}
		while(accumulator > ups)
		{
			accumulator -= ups;
			game.update();
		}
		window.clear();
		game.render();
		window.display();
		accumulator += clock.restart();
	}
	game.cleanup();
	luaclose();
	info("Clean Exit");
}

