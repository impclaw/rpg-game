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

class Player
{
public:
	Player(GameEngine*);
	Character party[4];
	int steps, kills, gold;
	MapObject* obj;
	int getx();
	int gety();
	void setmap(Map * map);
	void keydown(int key);
	void update();
	void render(GameEngine*);
private:
	bool leftdown, rightdown, updown, downdown;
	void createparty();

};

int xptolevel(int);
int leveltoxp(int);
