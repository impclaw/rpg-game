#pragma once
#include <SFML/Graphics.hpp>
#include "../gs.h"
#include "../res.h"
#include "../gui/xbutton.h"

class ItemMenuState : public GameState
{
public:
	ItemMenuState(GameEngine*);
	virtual void keypressed(GameEngine*, int key);
	virtual void pause();
	virtual void resume();
	virtual void updateitems(GameEngine*);
	virtual void update(GameEngine*);
	virtual void render(GameEngine*);
private:
	int getlocalpos();
	int getlowpos();
	int gethighpos();
	sf::RectangleShape * bg;
	sf::RectangleShape * hr;
	sf::RectangleShape * lowhr;
	sf::RectangleShape * scbar; //scrollbar bar
	sf::RectangleShape * scslider; //scrollbar slider
	sf::Text* desctxt;
	XButton* usebtn;
	XButton* arrangebtn;
	XButton* sortbtn;
	XButton* keybtn;
	bool slotvisible[32];
	sf::Sprite* itemicons[32];
	XButton* itembtns[32];
	sf::Text * itemnums[32];
	int menupos; //Menu Position (-1 = None)
		// 0 = Use
		// 1 = Arrange
		// 2 = Sort
		// 3 = Key
	int subpos; //Submenu Position
		// -1 = Not in submenu, but top menu
		// N > -1 = Cursor Item Position 
			// (0, 1)
			// (2, 3)
			// (4, 5)
	int charpos; // Char Position
		// -1 = Not selecting character
		// N > -1 = Character position
	int arrselect; // Item selected for arrange
};

