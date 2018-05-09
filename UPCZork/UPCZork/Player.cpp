#include "stdafx.h"

#include "Common.h"
#include "Player.h"
#include "Item.h"
#include "Room.h"


Player::Player(const char* _name, const char* _description, Room* _room) :
	Entity(_name, _description, (Entity*)_room)
{
	type = PLAYER;
	hitPoints = 5;
	victory = false;
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

	if (item->itemType == ARMOUR && armour != NULL)
	{
		if (Equals(item->name, armour->name))
			armour = NULL;
	}

	cout << "\n You drop ";
	StartKeyWord();
	cout << item->name;
	EndKeyWord();
	cout << "...\n\n";

	item->ChangeParentTo(parent);

	return true;
}

bool Player::Use(string & itemName)
{
	if (childs.size() == 0)
	{
		cout << "You do not have any items";
		return true;
	}

	for (list<Entity*>::const_iterator it = childs.begin(); it != childs.cend(); ++it)
	{
		Item * item = (Item *)(*it);

		if (Equals(item->name, itemName) && item->itemType == POTION)
		{
			hitPoints += item->power;

			cout << "\n You used ";
			StartKeyWord();
			cout << item->name;
			EndKeyWord();
			cout << " and heal " << item->power;
			if(item->power == 1)
				cout << " point\n\n";
			else
				cout << " points\n\n";

			return true;
		}

	}

	cout << " You can not use that item\n\n";
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
		if(item->power == 1)
			cout << "\n ) It has " << item->power << " point of damage\n\n";
		else
			cout << "\n ) It has " << item->power << " points of damage\n\n";
	}
	else if (item->itemType == ARMOUR)
	{
		if (item->power == 1)
			cout << "\n ) It gives me " << item->power << " point of protection\n\n";
		else
			cout << "\n ) It gives me " << item->power << " points of protection\n\n";
	}

	return true;
}

bool Player::Equip(string & itemName)
{
	for (list<Entity*>::const_iterator it = childs.begin(); it != childs.cend(); ++it)
	{
		if ((*it)->type == ITEM)
		{
			Item * _armour = (Item *)(*it);

			if (_armour->itemType == ARMOUR && Equals(_armour->name, itemName))
			{
				armour = _armour;
				cout << "\n You equipped ";
				StartKeyWord();
				cout << armour->name << "\n\n";
				EndKeyWord();

				return true;
			}

			if (_armour->itemType != ARMOUR && Equals(_armour->name, itemName))
			{
				cout << "\n I can not equip that item\n\n";
				return true;
			}
		}
	}

	cout << "\n I can not find that item";
	return true;
}

bool Player::Unequip(string & itemName)
{

	if (armour == NULL)
	{
		cout << "\n You dont have an armour equipped...\n\n";
		return true;
	}

	for (list<Entity*>::const_iterator it = childs.begin(); it != childs.cend(); ++it)
	{
		if ((*it)->type == ITEM)
		{
			Item * _armour = (Item *)(*it);

			if (Equals(armour->name, _armour->name))
			{
				armour = NULL;
				cout << "\n You unequipped ";
				StartKeyWord();
				cout << _armour->name << "\n\n";
				EndKeyWord();

				return true;
			}
		}
	}
	
	cout << "\n You dont have an armour of that name\n\n";
	return true;
}

void Player::Stats()
{
	cout << "\n I have:\n\n";
	cout << "  -HP  = " << hitPoints << "\n";
	if(armour != NULL)
		cout << "  -Def = " << armour->power << "\n\n";
	else 
		cout << "  -Def = 0\n\n";
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
		!Equals(direction, "West")  && !Equals(direction, "west")  &&
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

	if (actualRoom->IsDirectionBlockedByEnemies(direction)) 
	{
		return true;
	}

	cout << "\n You take the direction " << direction << "...\n\n";

	ChangeParentTo(actualRoom->GetRoomOfDirection(direction));

	parent->Look();

	if (Equals(parent->name, "Exit"))
		victory = true;

	return true;

}