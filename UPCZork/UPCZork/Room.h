#ifndef __Room__
#define __Room__

#include <iostream>
/*#include <string>
#include <list>*/

#include "Entity.h"

using namespace std;

class Room : public Entity
{

public:

	Room(const char* _name, const char* _description);
	~Room();

	void Look() override;
	bool Pick(string & itemName) override { return false; };
	bool Drop(string & itemName) override { return false; };
	bool Use()  override { return false; };
	void Action() override {};

	bool SetNeighbour(Room * room, const char * direction);
	bool isDirectionNull(string & direction);
	Room * GetRoomOfDirection(string & direction);

public:

	const char * directions[4] = {"North", "East", "West", "South"};

	Room * neighbours[4] = {NULL, NULL, NULL, NULL};


};

#endif
