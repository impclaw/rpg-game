#include "player.h"
#include "states/wander.h"

Character::Character()
{
	maxhp = hp = maxmp = mp = 0;
	xp = str = def = mag = agi = 0;
	active = false;
}


Player::Player(GameEngine* engine)
{
	createparty();
	steps = 0;
	kills = 0;
	gold = 50;
	obj = new MapObject(engine, "player");
	obj->centered = true;
}

void Player::createparty()
{
	party[0].name = "Player";
	party[0].cclass = "Computer Programmer";
	party[0].active = true;
	party[0].portrait = "player-face";
	party[0].xp = 42482;
}

int Player::getx()
{
	return obj->x;
}

int Player::gety()
{
	return obj->y;
}

void Player::keydown(int key)
{
	if(key == sf::Keyboard::Return)
	{
		int targetx = obj->mapx;
		int targety = obj->mapy;
		switch(obj->direction)
		{
			case 1: targety++; break;
			case 2: targetx--; break;
			case 3: targetx++; break;
			case 4: targety--; break;
		}
		MapObject * target = NULL;
		for(auto o : obj->parent->objects)
			if(targetx == o->mapx && targety == o->mapy)
				target = o;
		if(target != NULL)
		{
			obj->parent->activateobject(target);
		}
	}
}

void Player::update()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		downdown = true;
	else
		downdown = false;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		leftdown = true;
	else
		leftdown = false;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		rightdown = true;
	else
		rightdown = false;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		updown = true;
	else
		updown = false;
	
	if(downdown)
		obj->step(1);
	if(leftdown)
		obj->step(2);
	if(rightdown)
		obj->step(3);
	if(updown)
		obj->step(4);
	obj->update();
}

void Player::render(GameEngine* engine)
{
	obj->render(engine);
}

int xptolevel(int exp)
{
	return (int)(0.14 * sqrtf(exp));
}

int leveltoxp(int lvl)
{
	return (lvl/0.14f) * (lvl/0.14f);
}
