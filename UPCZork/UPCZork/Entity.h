#ifndef __Entity__
#define __Entity__

#include <string>
#include <list>

using namespace std;

enum Type
{
	PLAYER,
	ROOM,
	ITEM,
	ENEMY
};

class Entity
{

public:

	Entity(const char * _name, const char * _description, Entity * _parent);
	~Entity();

	virtual void Look();
	virtual bool Pick(string & itemName)   = 0;
	virtual bool Drop(string & itemName)   = 0;
	virtual bool Use()    = 0;
	virtual void Action() = 0;

	void ChangeParentTo(Entity * _parent);
	Entity * Find(const string & name, Type type) const;

public:

	Type   type;
	string name;
	string description;

	Entity * parent;
	list<Entity*> childs;

};

#endif