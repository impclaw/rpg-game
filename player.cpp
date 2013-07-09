#include "player.h"


Character::Character()
{
	maxhp = hp = maxmp = mp = 0;
	xp = str = def = mag = agi = 0;
	active = false;
}


Player::Player()
{
	createparty();
	x = y = 0;
	stepsleft = 0;
	walkstate = 0;
	steps = 0;
	kills = 0;
	gold = 50;
}

void Player::createparty()
{
	party[0].name = "Player";
	party[0].cclass = "Computer Programmer";
	party[0].active = true;
	party[0].portrait = "player-face";
	party[0].xp = 42482;
}

void Player::keydown(int key)
{
	if(walkstate == 0)
	{
		if(key == sf::Keyboard::Left)
		{
			walkstate = 1;
			stepsleft = 32;
		}
		if(key == sf::Keyboard::Up)
		{
			walkstate = 2;
			stepsleft = 32;
		}
		if(key == sf::Keyboard::Down)
		{
			walkstate = 3;
			stepsleft = 32;
		}
		if(key == sf::Keyboard::Right)
		{
			walkstate = 4;
			stepsleft = 32;
		}
	}
}

void Player::update()
{
	if(walkstate)
	{
		switch(walkstate)
		{
			case 1: x-=2; break;
			case 2: y-=2; break;
			case 3: y+=2; break;
			case 4: x+=2; break;
		}
		stepsleft-=2;
		if(stepsleft == 0)
			walkstate = 0;
	}
}

void Player::render(GameEngine* engine)
{
}

int xptolevel(int exp)
{
	return (int)(0.14 * sqrtf(exp));
}

int leveltoxp(int lvl)
{
	return (lvl/0.14f) * (lvl/0.14f);
}
