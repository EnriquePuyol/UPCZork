#ifndef __Item__
#define __Item__

#include <iostream>

#include "Entity.h"

class Room;

using namespace std;

enum ItemType
{
	KEY,
	WEAPON,
	CHEST,
	OTHER
};

class Item : public Entity
{

public:

	Item(const char* _name, const char* _description, Entity* _parent, ItemType _itemType = OTHER);
	~Item();

	void Look()   override;
	bool Pick(string & itemName) override;
	bool Drop(string & itemName) override;
	bool Use()    override;
	void Action() override;

	void AddTreasure(Entity * _treasure);

public:

	bool isLocked;

	ItemType itemType;

	list <Entity *> treasures;

};

#endif