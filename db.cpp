#include "db.h"
#include "gs.h"
#include "sys.h"

Database::Database(GameEngine * engine)
{
	std::string itemstxt = *(engine->resources->getText("items.txt"));
	std::vector<std::string> lines = split(itemstxt, '\n');
	items = new Item*[lines.size()];
	int n = 0;
	for(auto s : lines)
	{
		std::vector<std::string> tokens = split(s, ';');
		Item * i = new Item();
		i->id = atoi(tokens.at(0).c_str());
		i->name = tokens.at(1);
		i->icon = atoi(tokens.at(2).c_str());
		i->effect = atoi(tokens.at(3).c_str());
		i->arg1 = atoi(tokens.at(4).c_str());
		i->arg2 = atoi(tokens.at(5).c_str());
		i->description = tokens.at(6);
		items[n] = i;
		n++;
	}
	itemcount = n;
}

Database::~Database()
{
	for(int i = 0; i < itemcount; i++)
	{
		delete items[i];
	}
	delete[] items;
}

