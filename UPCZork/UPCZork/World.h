#ifndef __World__
#define __World__

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <time.h>

#define TICK_FREQUENCY 0.5f

using namespace std;

class Entity;
class Player;
class Room;
class Item;

class World
{

public:

	World();
	~World();

	bool RunGame();

	void CreateWorld();

	bool Action(vector<string>& args);
	bool ParseActions(vector<string>& args);
	void Wait();

public:

	clock_t timer;
	list<Entity *> rooms;
	list<Entity *> enemies;
	list<Entity *> items;
	Player * player;

};

#endif