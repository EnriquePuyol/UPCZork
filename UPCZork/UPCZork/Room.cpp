#include "stdafx.h"

#include "Room.h"
#include "Common.h"

Room::Room(const char* _name, const char* _description) : 
	Entity(_name, _description, NULL)
{
	type = ROOM;
}


Room::~Room()
{
}

void Room::Look()
{
	cout << "\n " << name << "\n ";
	cout << description;
	cout << "\n";

	// Neighbours
	for (int i = 0; i < 4; i++)
	{
		if (neighbours[i] != NULL) {
			cout << "\n At ";
			StartKeyWord();
			cout << directions[i];
			EndKeyWord();
			cout << " you see " << neighbours[i]->name;
		}
	}

	cout << "\n";

	// Items
	for (list<Entity*>::const_iterator _item = childs.begin(); _item != childs.cend(); _item++)
	{
		if ((*_item)->type == ITEM)
		{
			cout << "\n  -There is an item here: ";
			StartKeyWord(); 
			cout << (*_item)->name;
			EndKeyWord();
		}
	}

	cout << "\n";

	// Enemies
	for (list<Entity*>::const_iterator _enemy = childs.begin(); _enemy != childs.cend(); _enemy++)
	{
		if ((*_enemy)->type == ENEMY)
		{
			cout << "\n  ! You are not alone here: ";
			StartKeyWord(); 
			cout << (*_enemy)->name;
			EndKeyWord();
		}
	}

	cout << "\n\n";
}

bool Room::SetNeighbour(Room * room, const char * direction)
{
	if (direction == "North") 
	{
		neighbours[0] = room;
		return true;
	}
	else if (direction == "East")
	{
		neighbours[1] = room;
		return true;
	}
	else if (direction == "West")
	{
		neighbours[2] = room;
		return true;
	}
	else if (direction == "South")
	{
		neighbours[3] = room;
		return true;
	}

	return false;
}

bool Room::isDirectionNull(string & direction)
{
	if (Equals(direction, "North") || Equals(direction, "north"))
	{
		if (neighbours[0] == NULL)
			return true;
	}
	else if (Equals(direction, "East") || Equals(direction, "east"))
	{
		if (neighbours[1] == NULL)
			return true;
	}
	else if (Equals(direction, "West") || Equals(direction, "west"))
	{
		if (neighbours[2] == NULL)
			return true;
	}
	else if (Equals(direction, "South") || Equals(direction, "south"))
	{
		if (neighbours[3] == NULL)
			return true;
	}

	return false;
}

Room * Room::GetRoomOfDirection(string & direction)
{
	if (Equals(direction, "North") || Equals(direction, "north"))
		return neighbours[0];
	else if (Equals(direction, "East") || Equals(direction, "east"))
		return neighbours[1];
	else if (Equals(direction, "West") || Equals(direction, "west"))
		return neighbours[2];
	else if (Equals(direction, "South") || Equals(direction, "south"))
		return neighbours[3];
	
	return NULL;
}