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
	Room * room1	  = new Room("Clear", " This is where I woke up. It is a clear of a forest but \n  with the trees I can not see much");
	Room * room2	  = new Room("Lake", " There is a lake here, this place feels involved in a magical aura");
	Room * room3	  = new Room("Woods", " This is the center of the forest, I should  not get lost");
	Room * room4      = new Room("Mountain", " I am in the middle of the mountains, but I still can not find the exit");
	Room * room5	  = new Room("Entrance", " I am at the entrance of a big building made of stone");
	Room * room6	  = new Room("Treasure Room", " This room looks like an old treasure room, but it is almost empty");
	Room * room7	  = new Room("Cave", " This cave looks a bit warmer than outside, but it is not very deep");
	Room * room8	  = new Room("Exit", "I did it, I am out of this dangerous forest!!");

	rooms.push_back(brokenRoom);
	rooms.push_back(room1);
	rooms.push_back(room2);
	rooms.push_back(room3);
	rooms.push_back(room4);
	rooms.push_back(room5);
	rooms.push_back(room6);
	rooms.push_back(room7);
	rooms.push_back(room8);

	room1->SetNeighbour(room2, "West");
	room1->SetNeighbour(room3, "North");
	room2->SetNeighbour(room1, "East");
	room3->SetNeighbour(room1, "South");
	room3->SetNeighbour(room7, "East");
	room3->SetNeighbour(room4, "North");
	room4->SetNeighbour(room5, "West");
	room4->SetNeighbour(room3, "South");
	room5->SetNeighbour(room4, "East");
	room5->SetNeighbour(room6, "South");
	room6->SetNeighbour(room5, "North");
	room6->SetNeighbour(room3, "East");
	room7->SetNeighbour(room3, "West");
	room7->SetNeighbour(room8, "South");

	// Enemies
	Enemy * wolf = new Enemy("Wolf", "A hungry grey wolf", room2, 1, 1, 0);
	Enemy * ghost = new Enemy("Ghost_Wolf", "The wolf came back to life!!", brokenRoom, 2, 1, 0);
	wolf->afterDeathEnemy = ghost;
	Enemy * wildfire = new Enemy("Wildfire", "A living wilfire, looks furious", room7, 3, 1, 1);
	Enemy * corpse = new Enemy("Corpse", "This place is dangerous...", room3, 0, 0, 0);
	corpse->isAlive = false;
	Enemy * guard = new Enemy("Guard", "An ancient guard, how old is he/she?", room5, 5, 2, 1);
	guard->blockingExits[3] = true;
	Enemy * guard2 = new Enemy("Spectral_Guard", "He will defend this even death!", brokenRoom, 3, 3, 1);
	guard2->blockingExits[3] = true;
	guard->afterDeathEnemy = guard2;

	enemies.push_back(wolf);
	enemies.push_back(wildfire);
	enemies.push_back(corpse);
	enemies.push_back(guard);
	enemies.push_back(guard2);

	// Doors
	Enemy * door = new Enemy("Iron_Door", "A strong iron door", room1, 1, 0, 100);
	door->enemyType = DOOR;
	door->blockingExits[0] = true;
	door->id = 2;
	Enemy * door2 = new Enemy("Esmerald_Door", "A beautifull esmerald door, looks really heavy", room7, 1, 0, 100);
	door2->enemyType = DOOR;
	door2->blockingExits[2] = true;
	door2->id = 3;
	Enemy * ancientDoor = new Enemy("Ancient_Door", "This door has been close at least for a thousand years", room7, 100, 0, 100);
	ancientDoor->enemyType = DOOR;
	ancientDoor->id = 4;
	ancientDoor->blockingExits[3] = true;
	Enemy * secretDoor = new Enemy("Tunnel", "There is a tunnel here, where could this end?", room6, 1, 0, 100);
	secretDoor->enemyType = DOOR;
	secretDoor->id = 5;
	secretDoor->blockingExits[1] = true;

	enemies.push_back(door);
	enemies.push_back(door2);
	enemies.push_back(ancientDoor);
	enemies.push_back(secretDoor);

	// Items
	Item * chest = new Item("Wood_Chest", "A wooden chest, what could have inside?", room2, 1, CHEST);
	chest->isLocked = true;
	Item * sword = new Item("Sword", "An ordinary test sword", room1, 0, WEAPON);
	sword->power = 1;
	Item * key  = new Item("Wood_Key", "A simple key made of wood", wolf, 1, KEY);
	Item * key2 = new Item("Iron_Key", "A decorated iron key", chest, 2, KEY);
	Item * key3 = new Item("Esmerald_key", "A strange green key", wildfire, 3, KEY);
	Item * potion = new Item("Basic_Potion", "A simple potion to heal yourself 1 HP", chest, 0, POTION);
	potion->power = 1;
	Item * axe = new Item("Axe", "A lumberjack axe, it is really sharp", corpse, 0, WEAPON);
	axe->power = 2;
	Item * armour = new Item("Armor", "A simple armor made of leather", corpse, 0, ARMOUR);
	armour->power = 1;
	Item * potion2 = new Item("Superpotion", "This elixir could save my life any moment", room4, 0, POTION);
	potion2->power = 3;
	Item * chest2 = new Item("Gold_Chest", "If only I could carry this to the exit...", room6, 10, CHEST);
	Item * key4 = new Item("Ancient_Key", "This key looks as old as time itself", chest2, 4, KEY);
	Item * spear = new Item("Spear", "The spear of the ancient guard... It is so cool!!", guard, 0, WEAPON);
	spear->power = 5;
	Item * button = new Item("Magic_button", "What artifact is this?", room6, 5, KEY);

	items.push_back(chest);
	items.push_back(sword);
	items.push_back(key);
	items.push_back(key2);
	items.push_back(key3);
	items.push_back(potion);
	items.push_back(axe);
	items.push_back(potion2);
	items.push_back(chest2);
	items.push_back(key4);
	items.push_back(spear);

	// Player
	player = new Player("Hero", "I need to escape this place!", room1);

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
		else if (Equals(args[0], "equip"))
		{
			return player->Equip(args[1]);
		}
		else if (Equals(args[0], "unequip"))
		{
			return player->Unequip(args[1]);
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
			if (!enemy->isAlive)
			{
				cout << "\n The enemy is already dead\n\n";
				return true;
			}

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

				enemy->isAlive = false;

				if (enemy->afterDeathEnemy != NULL)
				{
					enemy->afterDeathEnemy->ChangeParentTo(enemy->parent);
					StartKeyWord();
					cout << "\n\n " <<enemy->afterDeathEnemy->name;
					EndKeyWord();
					cout << " appears from the corpe of ";
					StartKeyWord();
					cout << enemy->name;
					EndKeyWord();
					cout << "!";

				}

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
			}
			else 
			{
				int damage2 = (enemy->damage - player->armour->power);
				if (damage2 < 0)
					damage2 = 0;

				player->hitPoints -= damage2;

				cout << " ";
				StartKeyWord();
				cout << enemy->name;
				EndKeyWord();
				cout << " attacked you and dealt " << damage2 << " damage (Your armour blocked " << (enemy->damage - damage2) << ")\n\n";
			}			

			if (player->hitPoints <= 0)
			{
				StartKeyWord();
				cout << "\n "<< enemy->name;
				EndKeyWord();
				cout << " killed you!!! GAME OVER\n\n";
				return true;
			}

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
