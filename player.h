#pragma once
#include "res.h"
#include <math.h>

class GameEngine;

class Character
{
public:
	Character();
	bool active;
	int hp, maxhp, mp, maxmp;
	int str, def, mag, agi;
	int xp;
	std::string portrait;
	std::string name;
	std::string cclass;
};

class Player
{
public:
	Player();
	Character party[4];
	void keydown(int key);
	void update();
	void render(GameEngine*);
	int steps, kills, gold;
	int x, y;
	int walkstate;
	int stepsleft;
private:
	void createparty();

};

int xptolevel(int);
int leveltoxp(int);
