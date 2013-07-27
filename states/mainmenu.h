#pragma once
#include <SFML/Graphics.hpp>
#include "../gs.h"
#include "../player.h"
#include "../res.h"
#include "../sys.h"
#include "message.h"
#include "itemmenu.h"

enum MainMenuItem {
	MAINMENU_ITEMS,
	MAINMENU_SKILLS,
	MAINMENU_STATUS,
	MAINMENU_SAVE
};

class MainMenuState : public GameState
{
public:
	virtual void init(GameEngine*);
	virtual void keypressed(GameEngine*, int key);
	virtual void pause();
	virtual void resume();
	virtual void update(GameEngine*);
	virtual void render(GameEngine*);
	virtual ~MainMenuState();
	static const sf::Color outlinecolor;
	static const sf::Color lightfillcolor;
	static const sf::Color fillcolor;
	static const sf::Color darkfillcolor;
	static const sf::Color portraitcolor;

private:
	int arrowpos;
	int fadevalue;
	int fadedir; // 0 if no fade, -1 if fade out, 1 if fade in

	sf::Sprite *arrow;
	sf::RectangleShape* itembgs[5];
	sf::Text* itemtxt[5];

	sf::RectangleShape* charabgs[4];
	sf::RectangleShape* chimgbgs[4];
	sf::Sprite* chimg[4];
	sf::Text* chname[4];
	sf::Text* chhp[4];
	sf::Text* chmp[4];
	sf::Text* chxp[4];

	sf::RectangleShape* bg;
	sf::RectangleShape* smallbg;
	sf::Text* goldtxt;
	sf::Text* steptxt;
	sf::Text* killtxt;

	sf::RectangleShape* fade;
};
