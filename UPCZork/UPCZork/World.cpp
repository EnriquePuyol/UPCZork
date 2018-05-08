#include "stdafx.h"

#include "Common.h"
#include "World.h"
#include "Enemy.h"
#include "Player.h"
#include "Room.h"
#include "Item.h"

World::World()
{
	CreateWorld();
}


World::~World()
{
	// Items
	for (list<Entity*>::iterator _items = items.begin(); _items != items.end(); ++_items)
		delete *_items;
	items.clear();
	// Enemies
	for (list<Entity*>::iterator _enemies = enemies.begin(); _enemies != enemies.end(); ++_enemies)
		delete *_enemies;
	enemies.clear();
	// Rooms
	for (list<Entity*>::iterator _rooms = rooms.begin(); _rooms != rooms.end(); ++_rooms)
		delete *_rooms;
	rooms.clear();
}

bool World::RunGame() 
{
	return false;
}

void World::CreateWorld()
{
	// Rooms
	Room * room1 = new Room("Room 1", "You are in the beta room test!");
	Room * room2 = new Room("Room 2", "Your are in the magic room test!");
	rooms.push_back(room1);
	rooms.push_back(room2);

	room1->SetNeighbour(room2, "West");
	room2->SetNeighbour(room1, "East");

	// Enemies
	Enemy * wolf = new Enemy("Wolf", "A hungry grey wolf", room1, 1, 1, 0);

	enemies.push_back(wolf);

	// Items
	Item * chest = new Item("Wood_Chest", "A wooden chest, what could have inside?", room1, CHEST);
	//chest->isLocked = true;
	Item * sword = new Item("Sword", "An ordinary test sword", chest, WEAPON);
	Item * key = new Item("Wood_Key", "A simple key made of wood", wolf, KEY);

	items.push_back(sword);
	items.push_back(key);

	// Player
	player = new Player("Hero", "I am myself", room1);

}

bool World::Action(vector<string>& args)
{
	bool isCorrect = true;

	if (args.size() > 0 && args[0].length() > 0)
	{
		isCorrect = ParseActions(args);
	}

	Wait();

	return isCorrect;

}

bool World::ParseActions(vector<string>& args)
{

	cout << "\n";

	size_t numberOfArgs = args.size();

	if (numberOfArgs == 1)
	{
		if(Equals(args[0], "look"))
		{
			player->parent->Look();
			return true;
		}
		if (Equals(args[0], "inventory"))
		{
			player->Inventory();
			return true;
		}
	}
	else if (numberOfArgs == 2)
	{
		if (Equals(args[0], "look"))
		{
			if (Equals(args[1], "me"))
			{
				player->Look();
				return true;
			}
			else if (Equals(args[1], "room"))
			{
				player->parent->Look();
				return true;
			}
			else if (Equals(args[1], "inventory"))
			{
				player->Inventory();
				return true;
			}
			else
			{
				// Gets the name and description of the item or enemy
				for (list<Entity*>::const_iterator it = player->parent->childs.begin(); it != player->parent->childs.cend(); ++it)
				{
					if (Equals((*it)->name, args[1]))
					{
						(*it)->Look();
						return true;
					}
				}
			}
		}
		else if (Equals(args[0], "go"))
		{
			return player->Go(args[1]);
		}
		else if (Equals(args[0], "pick"))
		{
			return player->Pick(args[1]);
		}
		else if (Equals(args[0], "drop"))
		{
			return player->Drop(args[1]);
		}
	}
	else if (numberOfArgs == 3)
	{
		if (Equals(args[0], "look"))
		{
			if (Equals(args[2], "me"))
			{
				player->Look();
				return true;
			}
			else if (Equals(args[2], "room"))
			{
				player->parent->Look();
				return true;
			}
			else 
			{
				// Gets the name and description of the item or enemy
				for (list<Entity*>::const_iterator it = player->parent->childs.begin(); it != player->parent->childs.cend(); ++it)
				{
					if (Equals((*it)->name, args[2]))
					{
						(*it)->Look();
						return true;
					}
				}
			}
		}
		else if (Equals(args[0], "go"))
		{
			return player->Go(args[2]);
		}
		else if (Equals(args[0], "drop"))
		{
			return player->Drop(args[2]);
		}
	}
	else if (numberOfArgs == 4)
	{
		if (Equals(args[0], "pick"))
		{
			//Coger un objeto dentro de otro objeto
			Item* item = (Item*)player->parent->Find(args[3], ITEM);

			if (item != NULL)
			{
				if (Equals(args[3], item->name))
				{
					if (item->isLocked)
					{
						cout << "\n It is locked...\n\n";
						return true;
					}

					Item* subitem = (Item*)item->Find(args[1], ITEM);

					if (subitem == NULL)
					{
						cout << "\n " << item->name << " does not have '" << args[1] << "'.\n\n";
						return true;
					}

					cout << "\n You take " << subitem->name << " from " << item->name << ".\n\n";
					subitem->ChangeParentTo(player);
					return true;

				}
			}

			Enemy * enemy = (Enemy *)player->parent->Find(args[3], ENEMY);

			if (enemy != NULL)
			{
				if (Equals(args[3], enemy->name))
				{
					if (enemy->isAlive)
					{
						cout << "\n You should kill it first...\n\n";
						return true;
					}

					Item* subitem = (Item*)enemy->Find(args[1], ITEM);

					if (subitem == NULL)
					{
						cout << "\n " << enemy->name << " does not have '" << args[1] << "'.\n\n";
						return true;
					}

					cout << "\n You take " << subitem->name << " from " << enemy->name << ".\n\n";
					subitem->ChangeParentTo(player);
					return true;

				}
			}
		}
	}

	return false;
}

void World::Wait()
{
	clock_t now = clock();

	if ((now - timer) / CLOCKS_PER_SEC > TICK_FREQUENCY)
	{
		for (list<Entity*>::iterator it = enemies.begin(); it != enemies.end(); ++it)
			(*it)->Action();

		timer = now;
	}
}
