#include <SFML/Graphics.hpp>
#include "states/wander.h"
#include "gs.h"
#include "res.h"
#include "lua.h"

int main()
{
	GameEngine game;
	sf::Clock clock;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Test Game");
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(0);
	game.init(&window);
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
		window.clear();
		if(clock.getElapsedTime().asSeconds() > 1/60.0f)
		{
			game.update();
			clock.restart();
		}
		game.render();
		window.display();
	}
	game.cleanup();
}

