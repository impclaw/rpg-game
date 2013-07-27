#pragma once
#include <string>

class GameEngine;

class Item
{
public:
	int id; // identifier used in savegames, array index is used in gameplay
	std::string name; // name of item
	int icon; //number in icons.png file
	int effect; //items effect 
		// 1 Heals <arg1> HP <arg2> MP
		// 2 Revives and restores <arg1> HP <arg2> MP
		// 3 Removes <arg1> status effect
		// 10 Equipment <arg1> decides type
		//     1 Weapon str + <arg2>
		//     2 Armor def + <arg2>
		// 11 Accessory
	int arg1;
	int arg2;
	std::string description;
};

class Database
{
public:
	Database(GameEngine * engine);
	Item ** items;
};

