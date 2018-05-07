#include "stdafx.h"
#include "Item.h"


Item::Item(const char* _name, const char* _description, Entity* _parent, ItemType _itemType) :
	Entity(_name, _description, _parent), itemType(_itemType)
{
	type = ITEM;
}


Item::~Item()
{
}

void Item::Look()
{
	cout << "\n " << name << "\n ";
	cout << description << "\n";
}

bool Item::Pick(string & itemName)
{
	return false;
}

bool Item::Drop(string & itemName)
{
	return false;
}

bool Item::Use()
{
	return false;
}

void Item::Action()
{

}

void Item::AddTreasure(Entity * _treasure)
{
	treasures.push_back(_treasure);
}