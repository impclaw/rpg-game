#include "player.h"
#include "states/wander.h"

Character::Character()
{
	maxhp = hp = maxmp = mp = 0;
	xp = str = def = mag = agi = 0;
	active = false;
}


Player::Player(GameEngine* engine) : MapObject(engine, "player.png")
{
	createparty();
	steps = 0;
	kills = 0;
	gold = 50;
	centered = true;
}

void Player::createparty()
{
	party[0].name = "Player";
	party[0].cclass = "Computer Programmer";
	party[0].active = true;
	party[0].portrait = "player-face.png";
	party[0].xp = 42482;
}

void Player::keydown(int key)
{
	if(key == sf::Keyboard::Return)
	{
		int targetx = mapx;
		int targety = mapy;
		switch(direction)
		{
			case 1: targety++; break;
			case 2: targetx--; break;
			case 3: targetx++; break;
			case 4: targety--; break;
		}
		for(auto o : parent->objects)
		{
			if(targetx == o->mapx && targety == o->mapy && o->blocking)
				parent->activateobject(o);
			if(mapx == o->mapx && mapy == o->mapy && !o->blocking)
				parent->activateobject(o);
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
		step(1);
	if(leftdown)
		step(2);
	if(rightdown)
		step(3);
	if(updown)
		step(4);
	MapObject::update();
}

void Player::render(GameEngine* engine)
{
	MapObject::render(engine);
}

int xptolevel(int exp)
{
	return (int)(0.14 * sqrtf(exp));
}

int leveltoxp(int lvl)
{
	return (lvl/0.14f) * (lvl/0.14f);
}
