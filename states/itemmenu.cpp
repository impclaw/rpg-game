#include "itemmenu.h"
#include "mainmenu.h"

ItemMenuState::ItemMenuState(GameEngine* engine)
{
	bg = new sf::RectangleShape();
	bg->setPosition(200, 32);
	bg->setSize(sf::Vector2f(600-32, 600-32*2));
	bg->setOutlineThickness(2);
	bg->setFillColor(MainMenuState::fillcolor);
	bg->setOutlineColor(MainMenuState::outlinecolor);

	hr = new sf::RectangleShape(sf::Vector2f(600-32, 2));
	hr->setPosition(200, 86);
	lowhr = new sf::RectangleShape(sf::Vector2f(600-32, 2));
	lowhr->setPosition(200, 520);
	scbar = new sf::RectangleShape(sf::Vector2f(2, 600-32*6));
	scbar->setPosition(760, 86+12);
	scslider = new sf::RectangleShape(sf::Vector2f(8, 4));
	scslider->setPosition(760-4, 86+12);

	desctxt = new sf::Text("", engine->resources->mainfont, 26U);
	desctxt->setPosition(216, 520);

	usebtn = new XButton(engine, "Use",         216+108*0, 32+16, 100, 24);
	arrangebtn = new XButton(engine, "Arrange", 216+108*1, 32+16, 100, 24);
	sortbtn = new XButton(engine, "Sort",       216+108*2, 32+16, 100, 24);
	keybtn = new XButton(engine, "Key",         216+108*3, 32+16, 100, 24);

	for(int i = 0; i < 32; i++)
	{
		int bx = 216+(i%2)*270;
		int by = 32+48+16+(i/2)*26;
		itemicons[i] = new sf::Sprite(*(engine->resources->getTexture("icons.png")));
		itemicons[i]->setPosition(bx, by);
		//itemicons[i]->setScale(0.67, 0.67);
		itembtns[i] = new XButton(engine, "", bx+28, by, 260-28, 24);
		itemnums[i] = new sf::Text("", engine->resources->mainfont, 26U);
		itemnums[i]->setPosition(bx+240, by-8);
		slotvisible[i] = false;
	}

	menupos = 0;
	subpos = -1;
	arrselect = -1;
	charpos = -1;
	updateitems(engine);
}

int ItemMenuState::getlocalpos()
{
	if(subpos < 16)
		return subpos;
	else if (subpos >= 200-16)
		return subpos-(200-32);
	else 
		return subpos %2 == 0 ? 14 : 15;
}
int ItemMenuState::getlowpos()
{
	if(subpos < 16)
		return 0;
	else if (subpos >= 200-16)
		return 200-32;
	else 
		return (subpos - 14)/2*2;
}

int ItemMenuState::gethighpos()
{
	return 32;
}

void ItemMenuState::keypressed(GameEngine* engine, int key)
{
	//Handle different keypresses
	if(key == sf::Keyboard::Left)
	{
		if(subpos == -1 && menupos > 0)
			menupos--;
		if(subpos > -1 && menupos != 2 && subpos > 0)
			subpos--;
	}
	if(key == sf::Keyboard::Right)
	{
		if(subpos == -1 && menupos < 3)
			menupos++;
		if(subpos > -1 && menupos != 2 && subpos < 199)
			subpos++;
	}
	if(key == sf::Keyboard::Up)
	{
		if(subpos > -1 && menupos != 2 && subpos > 1)
			subpos-=2;
	}
	if(key == sf::Keyboard::Down)
	{
		if(subpos > -1 && menupos != 2 && subpos < 198)
			subpos+=2;
	}
	if(key == sf::Keyboard::Return)
	{
		if(subpos == -1)
		{
			if(menupos != 2)
				subpos = 0;
			else if(menupos == 2)
			{
				//Sort Items
			}
		}
		else if(subpos > -1)
		{
			if(menupos == 0)
			{
				//Execute an item
			}
			else if(menupos == 1)
			{
				if(arrselect == -1)
					arrselect = subpos;
				else
				{
					int tmp = engine->player->itemslots[arrselect];
					int tmpc = engine->player->itemcounts[arrselect];
					engine->player->itemslots[arrselect] = 
						engine->player->itemslots[subpos];
					engine->player->itemcounts[arrselect] = 
						engine->player->itemcounts[subpos];
					engine->player->itemslots[subpos] = tmp;
					engine->player->itemcounts[subpos] = tmpc;
					arrselect = -1;
					//updateitems(engine);
				}
			}
		}
	}
	if(key == sf::Keyboard::Escape)
	{
		if(subpos == -1)
			engine->popstate();
		else if (subpos > -1)
			subpos = -1;
	}

	//Update description
	if(subpos != -1 && menupos != -3)
	{
		if(engine->player->itemslots[subpos] != -1)
			desctxt->setString(engine->db->items[engine->player->itemslots[subpos]]->description);
		else
			desctxt->setString("");

		scslider->setPosition(760-4, 86+12+subpos*((600-32*6)/200.0f));
	}

	//Update items
	updateitems(engine);
}

void ItemMenuState::pause()
{

}

void ItemMenuState::resume()
{

}

void ItemMenuState::updateitems(GameEngine* engine)
{
	for(int i = 0; i < 32; i++)
	{
		int ip = getlowpos() + i;
		if(engine->player->itemslots[ip] != -1)
		{
			int n = engine->db->items[engine->player->itemslots[ip]]->icon;
			itemicons[i]->setTextureRect(sf::IntRect((n%16)*24, (n/16)*24, 24, 24));
			itembtns[i]->settext(engine->db->items[engine->player->itemslots[ip]]->name);
			itemnums[i]->setString(std::to_string(engine->player->itemcounts[ip]));
			slotvisible[i] = true;
		}
		else
		{
			itembtns[i]->settext("");
			slotvisible[i] = false;
		}
	}
}

void ItemMenuState::update(GameEngine*)
{
	usebtn->deactivate();
	arrangebtn->deactivate();
	sortbtn->deactivate();
	keybtn->deactivate();
	switch(menupos)
	{
		case 0: usebtn->activate(); break; 
		case 1: arrangebtn->activate(); break; 
		case 2: sortbtn->activate(); break; 
		case 3: keybtn->activate(); break; 
	}
	for(int i = 0; i < 32; i++)
		itembtns[i]->deactivate();
	if(subpos > -1)
		itembtns[getlocalpos()]->activate();

}

void ItemMenuState::render(GameEngine* engine)
{
	engine->window->draw(*bg);
	engine->window->draw(*hr);
	engine->window->draw(*lowhr);
	engine->window->draw(*desctxt);
	engine->window->draw(*scbar);
	engine->window->draw(*scslider);
	usebtn->render(engine);
	arrangebtn->render(engine);
	sortbtn->render(engine);
	keybtn->render(engine);
	if(menupos != 3)
	{
		for(int i = 0; i < 32; i++)
		{
			itembtns[i]->render(engine);
			if(slotvisible[i])
			{
				engine->window->draw(*itemicons[i]);
				engine->window->draw(*itemnums[i]);
			}
		}
	}
}

