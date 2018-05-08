#include "stdafx.h"

#include "Common.h"
#include "Player.h"
#include "Item.h"
#include "Room.h"


Player::Player(const char* _name, const char* _description, Room* _room) :
	Entity(_name, _description, (Entity*)_room)
{
	type = PLAYER;
}


Player::~Player()
{
}

void Player::Look()
{
	cout << "\n " << name << "\n ";
	cout << description << "\n";
}

bool Player::Pick(string & itemName)
{

	Item* item = (Item*)parent->Find(itemName, ITEM);

	if (item == NULL)
	{
		cout << "\n I can not find that item\n\n";
		return true;
	}
	if (item->itemType == CHEST)
	{
		cout << "\n I can not pick that\n\n";
		return true;
	}
	else
	{
		cout << "\n You take ";
		StartKeyWord(); 
		cout << item->name;
		EndKeyWord(); 
		cout << ".\n\n";
		item->ChangeParentTo(this);
		return true;
	}

	return false;
}

bool Player::Drop(string & itemName)
{

	Item * item = (Item*)Find(itemName, ITEM);

	if (item == NULL)
	{
		cout << "\n You have no item with that name.\n\n";
		return true;
	}

	cout << "\n You drop ";
	StartKeyWord();
	cout << item->name;
	EndKeyWord();
	cout << "...\n\n";

	item->ChangeParentTo(parent);

	return true;
}

bool Player::Use()
{
	return false;
}

void Player::Action()
{

}

bool Player::Examine(string & itemName)
{

	Item* item = (Item*)Find(itemName, ITEM);

	if (item == NULL)
	{
		cout << "\n You have no item with that name.\n\n";
		return true;
	}

	StartKeyWord();
	cout << "\n " << item->name;
	EndKeyWord();
	if (item->itemType == WEAPON)
	{
		cout << "\n ) It has " << item->damage << " point of damage\n\n";
	}

	return true;
}

bool Player::Equip()
{
	return false;
}

void Player::Inventory()
{
	list<Entity*> items;
	for (list<Entity*>::const_iterator it = childs.begin(); it != childs.cend(); ++it)
	{
		if ((*it)->type == ITEM)
			items.push_back(*it);
	}

	if (items.size() == 0)
	{
		cout << "\n Your inventory is empty\n\n";
		return;
	}

	for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
	{
		if ((*it)->type == ITEM)
		{
			cout << "\n  - You have a ";
			StartKeyWord();
			cout << (*it)->name;
			EndKeyWord();
		}
	}
	cout << "\n\n";
}

bool Player::Go(string & direction)
{
	if (!Equals(direction, "North") && !Equals(direction, "north") &&
		!Equals(direction, "South") && !Equals(direction, "south") &&
		!Equals(direction, "West")  && !Equals(direction, "west") &&
		!Equals(direction, "East")  && !Equals(direction, "east"))
	{
		return false;
	}

	Room * actualRoom = (Room*)parent;

	if (actualRoom->IsDirectionNull(direction))
	{
		cout << "\n You can not go in that direction\n\n";
		return true;
	}

	if (actualRoom->GetRoomOfDirection(direction)->isLocked)
	{
		cout << "\n That direction is locked\n\n";
		return true;
	}

	cout << "\n You take the direction " << direction << "...\n\n";

	ChangeParentTo(actualRoom->GetRoomOfDirection(direction));

	parent->Look();

	return true;

}