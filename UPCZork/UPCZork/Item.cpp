#include "stdafx.h"
#include "Common.h"
#include "Item.h"


Item::Item(const char* _name, const char* _description, Entity* _parent, ItemType _itemType) :
	Entity(_name, _description, _parent), itemType(_itemType)
{
	type = ITEM;
	isLocked = false;
}


Item::~Item()
{
}

void Item::Look()
{
	cout << "\n " << name << "\n ";
	cout << description << "\n";

	if (!isLocked)
	{
		for (list<Entity*>::const_iterator it = childs.begin(); it != childs.cend(); ++it)
		{
			if ((*it)->type == ITEM)
			{
				cout << "\n  -It has a ";
				StartKeyWord();
				cout << (*it)->name;
				EndKeyWord();
				cout << " inside\n";
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
