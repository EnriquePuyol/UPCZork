#include "stdafx.h"
#include "Common.h"
#include "Item.h"


Item::Item(const char* _name, const char* _description, Entity* _parent, int _id, ItemType _itemType) :
	Entity(_name, _description, _parent), itemType(_itemType)
{
	type = ITEM;
	isLocked = false;
	id = _id;
}


Item::~Item()
{
}

void Item::Look()
{
	StartKeyWord();
	cout << "\n " << name << "\n ";
	EndKeyWord();

	if (itemType == WEAPON)
	{
		if (power == 1)
			cout << "\n -It has " << power << " point of damage\n\n";
		else
			cout << "\n -It has " << power << " points of damage\n\n";
	}

	if (!isLocked)
	{
		if (childs.size() == 0 && itemType == CHEST)
		{
			cout << " It is empty";
		}

		for (list<Entity*>::const_iterator it = childs.begin(); it != childs.cend(); ++it)
		{
			if ((*it)->type == ITEM)
			{
				cout << "\n  -It has a ";
				StartKeyWord();
				cout << (*it)->name;
				EndKeyWord();
				cout << " inside";
			}
		}
		cout << "\n\n";
	}
	else
	{
		cout << " It is locked\n\n";
	}

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
