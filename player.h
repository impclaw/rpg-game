#pragma once
#include <math.h>
#include "res.h"
#include "mapobject.h"
#include "gs.h"

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

class Player : public MapObject
{
public:
	Player(GameEngine*);
	~Player();
	Character party[4];
	int steps, kills, gold;
	void keydown(int key);
	void update();
	void render(GameEngine*);
	int itemslots[200];
	int itemcounts[200];
private:
	bool leftdown, rightdown, updown, downdown;
	bool walkdone;
	void createparty();

};

int xptolevel(int);
int leveltoxp(int);
