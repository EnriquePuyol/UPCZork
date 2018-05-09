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

void World::CreateWorld()
{
	// Rooms
	Room * brokenRoom = new Room("BrokenRoom", "Unavailable room to keep the items that breaks");
	Room * room1	  = new Room("Room_1", "You are in the beta room test!");
	Room * room2	  = new Room("Room_2", "You are in the magic room test!");
	Room * room3	  = new Room("Room_3", "You are in the north demo test!");
	Room * room4      = new Room("Room_4", "You are in one of the final rooms");
	Room * room5	  = new Room("Room_5", "You are in one of the final rooms");
	Room * room6	  = new Room("Room_6", "You are in one of the final rooms");
	Room * room7	  = new Room("Room_7", "You are in one of the final rooms");

	rooms.push_back(brokenRoom);
	rooms.push_back(room1);
	rooms.push_back(room2);
	rooms.push_back(room3);
	rooms.push_back(room4);
	rooms.push_back(room5);
	rooms.push_back(room6);
	rooms.push_back(room7);

	room1->SetNeighbour(room2, "West");
	room1->SetNeighbour(room3, "North");
	room2->SetNeighbour(room1, "East");
	room3->SetNeighbour(room1, "South");
	room3->SetNeighbour(room6, "West");
	room3->SetNeighbour(room7, "East");
	room3->SetNeighbour(room4, "North");
	room4->SetNeighbour(room5, "West");
	room4->SetNeighbour(room3, "South");
	room5->SetNeighbour(room4, "East");
	room5->SetNeighbour(room6, "South");
	room6->SetNeighbour(room5, "North");
	room6->SetNeighbour(room3, "East");
	room7->SetNeighbour(room3, "West");

	// Enemies
	Enemy * wolf = new Enemy("Wolf", "A hungry grey wolf", room2, 1, 1, 0);
	Enemy * door = new Enemy("Iron_Door", "A strong iron door", room1, 1, 0, 100);
	door->enemyType = DOOR;
	door->blockingExits[0] = true;
	door->id = 2;
	//wolf->blockingExits[2] = true;
	enemies.push_back(wolf);

	// Items
	Item * chest = new Item("Wood_Chest", "A wooden chest, what could have inside?", room2, 1, CHEST);
	chest->isLocked = true;
	Item * sword = new Item("Sword", "An ordinary test sword", room1, 0, WEAPON);
	sword->power = 1;
	Item * key  = new Item("Wood_Key", "A simple key made of wood", wolf, 1, KEY);
	Item * key2 = new Item("Iron_Key", "A decorated iron key", chest, 2, KEY);
	Item * potion = new Item("Basic_Potion", "A simple potion to heal yourself 1 HP", chest, 0, POTION);
	potion->power = 1;
	//Item * key2 = new Item("Iron_Key", "A rusty old iron key", wolf, 2, KEY);

	items.push_back(chest);
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
		else if (Equals(args[0], "inventory"))
		{
			player->Inventory();
			return true;
		}
		else if (Equals(args[0], "stats"))
		{
			player->Stats();
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
				for (int i = 0; i < 4; i++)
				{
					Room * actualRoom = (Room *)player->parent;
					if (Equals(args[1], actualRoom->directions[i]))
					{
						actualRoom->Look(args[1]);
						return true;
					}
				}

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
		else if (Equals(args[0], "examine"))
		{
			return player->Examine(args[1]);
		}
		else if (Equals(args[0], "attack"))
		{
			cout << "\n I need something to attack it with\n\n";
			return true;
		}
		else if (Equals(args[0], "use"))
		{
			return player->Use(args[1]);
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

					cout << "\n You take ";
					StartKeyWord();
					cout << subitem->name;
					EndKeyWord();
					cout << " from ";
					StartKeyWord(); 
					cout << item->name;
					EndKeyWord();
					cout << ".\n\n";
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

					cout << "\n You take ";
					StartKeyWord(); 
					cout << subitem->name;
					EndKeyWord(); 
					cout << " from ";
					StartKeyWord(); 
					cout << enemy->name; EndKeyWord();
					cout << ".\n\n";
					subitem->ChangeParentTo(player);
					return true;

				}
			}
		}
		else if (Equals(args[0], "unlock"))
		{
			//Coger un objeto dentro de otro objeto
			Item * item1 = (Item *)player->parent->Find(args[1], ITEM);  // Chest
			Enemy* door = (Enemy *)player->parent->Find(args[1], ENEMY); // Door
			Item * item2 = (Item*)player->Find(args[3], ITEM);		     // Keys

			if (item1 == NULL && door == NULL)
			{
				cout << "\n\n Cannot find '" << args[1] << "'\n\n";
				return true;
			}
			if (item2 == NULL)
			{
				cout << "\n\n I do not own '" << args[3] << "'\n\n";
				return true;
			}

			if (item1 != NULL && item1->id == item2->id && item1->id != 0)
			{
				Room * actualRoom = (Room *)player->parent;

				if (actualRoom->AreEnemiesAlive())
				{
					cout << "\n Can not unlock while enemies are alive...\n\n";
					return true;
				}

				item1->isLocked = false;
				item2->ChangeParentTo(rooms.front());
				cout << "\n The ";
				StartKeyWord();
				cout << item1->name;
				EndKeyWord();
				cout << " has been unlocked.\n";

				StartKeyWord();
				cout << " " << item2->name;
				EndKeyWord();
				cout << " has broken.\n\n";

				return true;
			}

			if (door != NULL && door->id == item2->id && door->id != 0)
			{
				Room * actualRoom = (Room *)player->parent;

				if (actualRoom->AreEnemiesAlive())
				{
					cout << "\n Can not unlock while enemies are alive...\n\n";
					return true;
				}

				for (int i = 0; i < 4; i++)
					door->blockingExits[i] = false;
				item2->ChangeParentTo(rooms.front());

				cout << "\n The ";
				StartKeyWord();
				cout << door->name;
				EndKeyWord();
				cout << " has been unlocked.\n";

				StartKeyWord();
				cout << " " << item2->name;
				EndKeyWord();
				cout << " has broken.\n\n";

				return true;
			}

			if (item1 != NULL)
			{
				cout << "\n The ";
				StartKeyWord();
				cout << item1->name;
				EndKeyWord();
				cout << " can not be unlocked with ";
				StartKeyWord();
				cout << item2->name;
				EndKeyWord();
				cout << "\n\n";

				return true;
			}
			
			cout << "\n The ";
			StartKeyWord();
			cout << door->name;
			EndKeyWord();
			cout << " can not be unlocked with ";
			StartKeyWord();
			cout << item2->name;
			EndKeyWord();
			cout << "\n\n";

			return true;

		}
		else if (Equals(args[0], "attack"))
		{
			Room * actualRoom = (Room *)player->parent;

			//Encontrar enemigo
			Enemy * enemy = (Enemy *)actualRoom->Find(args[1], ENEMY);
			if (enemy == NULL)
			{
				cout << "\n That enemy is not on this room\n\n";
				return true;
			}
			if (enemy->enemyType == DOOR)
			{
				cout << "\n I can not attack a door...\n\n";
				return true;
			}

			//Encontrar objeto
			Item* weapon = (Item*)player->Find(args[3], ITEM);

			if (weapon == NULL)
			{
				cout << "\n That enemy is not on this room\n\n";
				return true;
			}

			//Restarle vida al enemigo
			int damage = (weapon->power - enemy->armour);
			if (damage < 0)
				damage = 0;
			enemy->hitPoints -= damage;
			cout << "\n You did " << damage << " damage to ";
			StartKeyWord();
			cout << enemy->name;
			EndKeyWord();
			if (enemy->armour > 0)
				cout << " (his armour blocked "<< (weapon->power - damage) << " damage)";

			cout << "\n";

			if (enemy->hitPoints <= 0)
			{
				enemy->isAlive = false;
				for (int i = 0; i < 4; i++)
					enemy->blockingExits[i] = false;

				cout << " You killed ";
				StartKeyWord();
				cout << enemy->name;
				EndKeyWord();
				cout << "\n\n";
				return true;
			}
			
			//Restarme vida a mi
			if (player->armour == NULL)
			{
				player->hitPoints -= enemy->damage;

				cout << " ";
				StartKeyWord();
				cout << enemy->name;
				EndKeyWord();
				cout << " attacked you and dealt " << enemy->damage << " damage\n\n";
				return true;
			}

			player->hitPoints -= (enemy->damage - player->armour->power);

			cout << " ";
			StartKeyWord();
			cout << enemy->name;
			EndKeyWord();
			cout << " attacked you and dealt " << enemy->damage << " damage\n\n";

			return true;
		}
		else if (Equals(args[0], "use"))
		{
			if (Equals(args[3], "me"))
			{
				return player->Use(args[1]);
			}
		}
		else if (Equals(args[0], "put"))
		{
			//Coger un objeto dentro mi para dejarlo
			Item* item = (Item*)player->Find(args[1], ITEM);

			if (item == NULL)
			{
				cout << "\n\n You do not own that item\n\n";
				return true;
			}

			//El chest
			Item* chest = (Item*)player->parent->Find(args[3], ITEM);

			if (chest == NULL)
			{
				cout << "\n\n There is no where to put it\n\n";
				return true;
			}
			if (chest->isLocked)
			{
				cout << "\n\n That chest is locked\n\n";
				return true;
			}
			
			item->ChangeParentTo(chest);
			cout << "\n\n You put ";
			StartKeyWord();
			cout << item->name;
			EndKeyWord();
			cout << " in ";
			StartKeyWord();
			cout << chest->name << "\n\n";
			EndKeyWord();

			return true;

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
