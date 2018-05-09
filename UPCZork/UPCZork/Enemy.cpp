#include "stdafx.h"
#include "Common.h"
#include "Enemy.h"
#include "Room.h"


Enemy::Enemy(const char* _name, const char* _description, Room* _room, int _hitpoints, int _damage, int _armour) :
	Entity(_name, _description, (Entity*)_room)
{
	type = ENEMY;
	enemyType = NORMAL;
	id = 0;
	isAlive = true;
	hitPoints = _hitpoints;
	damage = _damage;
	armour = _armour;
}


Enemy::~Enemy()
{
}

void Enemy::Look()
{
	if (isAlive) 
	{
		cout << "\n " << description << "\n";

		if (enemyType == DOOR)
		{
			for (int i = 0; i < 4; i++)
			{
				if (blockingExits[i])
				{
					Room * actualRoom = (Room *)parent;

					cout << " It is blocking the ";
					StartKeyWord();
					cout << actualRoom->directions[i];
					EndKeyWord();
					cout << " way\n\n";

					return;
				}
			}

			return;
		}

		cout << "\n -It has ";
		if (hitPoints == 1)
			cout << hitPoints << " point of HP,\n";
		else
			cout << hitPoints << " points of HP,\n";
		if (damage == 1)
			cout << "         " << damage << " point of Damage and\n";
		else
			cout << "         " << damage << " points of Damage and\n";
		if (armour == 1)
			cout << "         " << armour << " point of Armour\n\n";
		else
			cout << "         " << armour << " points of Armour\n\n";

		for (list<Entity*>::const_iterator it = childs.begin(); it != childs.cend(); ++it)
		{
			if ((*it)->type == ITEM)
			{
				cout << "\n  - Looks like it has a ";
				StartKeyWord();
				cout << (*it)->name;
				EndKeyWord();
			}
		}
		cout << "\n\n";
	}
	else
	{
		cout << "\n Here lies ";
		StartKeyWord();
		cout << name;
		EndKeyWord();
		cout << " dead...";

		for (list<Entity*>::const_iterator it = childs.begin(); it != childs.cend(); ++it)
		{
			if ((*it)->type == ITEM)
			{
				cout << "\n  -Looks like it has a ";
				StartKeyWord();
				cout << (*it)->name;
				EndKeyWord();
			}
		}
		cout << "\n\n";
	}
}

bool Enemy::Pick(string & itemName)
{
	return false;
}

bool Enemy::Drop(string & itemName)
{
	return false;
}

bool Enemy::Use()
{
	return false;
}

void Enemy::Action()
{

}

int Enemy::Attack()
{
	return damage;
}

Room * Enemy::GetRoom()
{
	return (Room *)parent;
}

void Enemy::AddTreasure(Item * _treasure)
{
	treasures.push_back(_treasure);
}