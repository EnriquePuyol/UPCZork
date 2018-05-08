#ifndef __Player__
#define __Player__

#include <iostream>

#include "Entity.h"
#include "Item.h"

using namespace std;

class Room;

class Player : public Entity
{

public:

	Player(const char* _name, const char* _description, Room* _room);
	~Player();

	void Look() override;
	bool Pick(string & itemName) override;
	bool Drop(string & itemName) override;
	bool Use (string & itemName);
	bool Use()  override;
	void Action() override;
	bool Examine(string & itemName);
	bool Equip();

	void Stats();
	void Inventory();
	bool Go(string & direction);

public:

	int hitPoints;
	Item * armour;

};

#endif