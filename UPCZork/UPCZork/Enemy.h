#ifndef __Creature__
#define __Creature__

#include <iostream>

#include "Entity.h"

class Room;
class Item;

using namespace std;

enum EnemyType
{
	NORMAL,
	DOOR
};

class Enemy : public Entity
{

public:

	Enemy(const char* _name, const char* _description, Room* _room, int _hitpoints, int _damage, int _armour);
	~Enemy();

	void Look()   override;
	bool Pick(string & itemName)   override;
	bool Drop(string & itemName)   override;
	bool Use()    override;
	void Action() override;

	int  Attack();

	bool GetIsAlive()   { return isAlive; }
	int  GetHitPoints() { return hitPoints; }
	int  GetArmour()    { return armour; }
	int  GetDamage()    { return damage; }
	Room * GetRoom();

	void AddTreasure(Item * _treasure);
	void SetAfterDeathEnemy(Enemy * _enemy) { afterDeathEnemy = _enemy; }

public:

	int id;
	EnemyType enemyType;

	bool isAlive;
	bool blockingExits[4] = {false, false, false, false};

	int hitPoints;
	int armour;
	int damage;

	list<Item *> treasures;
	Enemy * afterDeathEnemy;

};

#endif