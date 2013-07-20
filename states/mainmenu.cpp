#include "mainmenu.h"

const sf::Color MainMenuState::outlinecolor (210, 210, 250, 255);
const sf::Color MainMenuState::fillcolor (65, 65, 230, 255);
const sf::Color MainMenuState::darkfillcolor (35, 35, 125, 255);
const sf::Color MainMenuState::portraitcolor (45, 45, 180, 255);

void MainMenuState::init(GameEngine* engine)
{
	arrow = new sf::Sprite(*(engine->resources->getTexture("menuarrow.png")));
	arrowpos = 0;
	fadevalue = 255;
	fadedir = 1;
	for(int i = MAINMENU_ITEMS; i <= MAINMENU_SAVE; i++)
	{
		itembgs[i] = new sf::RectangleShape();
		itembgs[i]->setSize(sf::Vector2f(160, 28));
		itembgs[i]->setPosition(8, 8+i*30);
		itembgs[i]->setOutlineThickness(2);
		itembgs[i]->setFillColor(fillcolor);
		itembgs[i]->setOutlineColor(outlinecolor);

		std::string text;
		switch(i)
		{
			case MAINMENU_ITEMS: text = "Items"; break;
			case MAINMENU_SKILLS: text = "Skills"; break;
			case MAINMENU_STATUS: text = "Status"; break;
			case MAINMENU_SAVE: text = "Save"; break;
		}
		itemtxt[i] = new sf::Text(text, engine->resources->mainfont, 32U);
		itemtxt[i]->setPosition(8+42, 8+i*30-10);
	}
	for(int i = 0; i < 4; i++)
	{
		charabgs[i] = new sf::RectangleShape();
		charabgs[i]->setSize(sf::Vector2f((800-160-24), (600)/4-8-2));
		charabgs[i]->setPosition(160+16, 8+i*(600/4-2));
		charabgs[i]->setOutlineThickness(2);
		charabgs[i]->setFillColor(fillcolor);
		charabgs[i]->setOutlineColor(outlinecolor);

		chimgbgs[i] = new sf::RectangleShape();
		int sz = (600/4-28);
		chimgbgs[i]->setSize(sf::Vector2f(sz, sz));
		int chimgx = 160+16+8; int chimgy = 8+i*(600/4-2)+8;
		chimgbgs[i]->setPosition(chimgx, chimgy);
		chimgbgs[i]->setOutlineThickness(1);
		chimgbgs[i]->setFillColor(portraitcolor);
		chimgbgs[i]->setOutlineColor(outlinecolor);

		Character * chara = &(engine->player->party[i]);
		if(chara->active)
		{
			chimg[i] = new sf::Sprite(*(engine->resources->getTexture(chara->portrait)));
			chimg[i]->setScale(sz/100.0f, sz/100.0f);
			chimg[i]->setPosition(chimgx, chimgy);
			chname[i] = new sf::Text(
				chara->name + "\t" + chara->cclass, engine->resources->mainfont, 32U);
			chhp[i] = new sf::Text(
				"HP: " + itos(chara->hp) + " / " + itos(chara->maxhp), 
				engine->resources->mainfont, 32U);
			chmp[i] = new sf::Text(
				"MP: " + itos(chara->mp) + " / " + itos(chara->maxmp), 
				engine->resources->mainfont, 32U);
			chxp[i] = new sf::Text(
				"Level: " + itos(xptolevel(chara->xp)) + "\t"
				"Next: " + itos(chara->xp - leveltoxp(xptolevel(chara->xp))), 
				engine->resources->mainfont, 32U);
			chname[i]->setPosition(chimgx+sz+16, chimgy);
			chhp[i]->setPosition(chimgx+sz+16, chimgy+32);
			chmp[i]->setPosition(chimgx+sz+16, chimgy+64);
			chxp[i]->setPosition(chimgx+sz+200, chimgy+32);
		}
	}
	bg = new sf::RectangleShape();
	bg->setSize(sf::Vector2f(800, 600));
	bg->setPosition(0, 0);
	bg->setFillColor(darkfillcolor);

	smallbg = new sf::RectangleShape();
	int h = 80;
	smallbg->setSize(sf::Vector2f(160, h));
	smallbg->setPosition(8, 600-h-8);
	smallbg->setOutlineThickness(2);
	smallbg->setFillColor(fillcolor);
	smallbg->setOutlineColor(outlinecolor);

	std::string gold = "Gold: " + itos(engine->player->gold);
	std::string steps = "Steps: " + itos(engine->player->steps);
	std::string kills = "Kills: " + itos(engine->player->steps);
	goldtxt = new sf::Text(gold, engine->resources->mainfont, 32U);
	goldtxt->setPosition(16, 600-h-16);
	steptxt = new sf::Text(steps, engine->resources->mainfont, 32U);
	steptxt->setPosition(16, 600-h+8);
	killtxt = new sf::Text(kills, engine->resources->mainfont, 32U);
	killtxt->setPosition(16, 600-h+32);

	fade = new sf::RectangleShape();
	fade->setSize(sf::Vector2f(800, 600));
	fade->setPosition(0, 0);
	fade->setFillColor(sf::Color::Black);
}

void MainMenuState::keypressed(GameEngine* engine, int key)
{
	if(key == sf::Keyboard::Up && arrowpos > 0)
		arrowpos--;
	if(key == sf::Keyboard::Down && arrowpos < MAINMENU_SAVE)
		arrowpos++;
	if(key == sf::Keyboard::Escape && fadedir == 0)
	{
		fadevalue = 0;
		fadedir = -1;
	}
	if(key == sf::Keyboard::Return)
	{
		if(arrowpos == MAINMENU_SAVE)
		{
			MessageState *ms = new MessageState(engine, "Savegame", "Your game has been saved. \nJust kidding! Saving is not implemented yet! \nPress enter to continue. ", 2);
			engine->pushstate(ms);
		}
	}
}

void MainMenuState::update(GameEngine* engine)
{
	arrow->setPosition(8+4, 8+arrowpos*30 + 2);
	if(fadedir == 1)
		fadevalue -= 10;
	if(fadedir == -1)
		fadevalue += 10;
	if(fadevalue < 0)
	{
		fadevalue = 0;
		fadedir = 0;
	}
	if(fadevalue > 255)
	{
		engine->popstate();
		return;
	}
	//fprintf(stderr, "%d %d\n", fadevalue, fadedir);
	sf::Color fadecolor(0, 0, 0, fadevalue);
	fade->setFillColor(fadecolor);
}
void MainMenuState::render(GameEngine* engine)
{
	engine->window->draw(*bg);
	for(int i = MAINMENU_ITEMS; i <= MAINMENU_SAVE; i++)
	{
		engine->window->draw(*itembgs[i]);
		engine->window->draw(*itemtxt[i]);
	}
	for(int i = 0; i < 4; i++)
	{
		engine->window->draw(*charabgs[i]);
		engine->window->draw(*chimgbgs[i]);
		if(engine->player->party[i].active)
		{
			engine->window->draw(*chimg[i]);
			engine->window->draw(*chname[i]);
			engine->window->draw(*chhp[i]);
			engine->window->draw(*chmp[i]);
			engine->window->draw(*chxp[i]);
		}
	}
	engine->window->draw(*smallbg);
	engine->window->draw(*goldtxt);
	engine->window->draw(*steptxt);
	engine->window->draw(*killtxt);
	engine->window->draw(*arrow);
	engine->window->draw(*fade);
}

MainMenuState::~MainMenuState()
{
	for(int i = MAINMENU_ITEMS;i <= MAINMENU_SAVE; i++)
	{
		delete itembgs[i];
		delete itemtxt[i];
	}
	for (int i = 0; i < 4; i++) 
	{
		delete charabgs[i];
		delete chimgbgs[i];
		if(chimg[i] != NULL)
		{
			delete chimg[i];
			delete chname[i];
			delete chhp[i];
			delete chmp[i];
			delete chxp[i];
		}
	}
	delete smallbg;
	delete goldtxt;
	delete steptxt;
	delete killtxt;
	delete arrow;
	delete fade;
}
void MainMenuState::pause()
{
}
void MainMenuState::resume()
{
}
