#include "gs.h"

class MapObject
{
public:
	MapObject(GameEngine *, std::string);
	void update(GameEngine *);
	void render(GameEngine *);
	void step(int dir);
};

