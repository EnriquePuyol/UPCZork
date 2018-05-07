#include "stdafx.h"

#include <iostream>
#include "Common.h"
#include "Entity.h"


Entity::Entity(const char * _name, const char * _description, Entity * _parent = NULL) :
	name(_name), description(_description), parent(_parent)
{
	if (_parent != NULL)
	{
		parent->childs.push_back(this);
	}
}


Entity::~Entity()
{
}

void Entity::Look() { }

void Entity::ChangeParentTo(Entity* _parent)
{
	if (parent != NULL)
		parent->childs.remove(this);

	parent = _parent;

	if (parent != NULL)
		parent->childs.push_back(this);
}

Entity* Entity::Find(const string& name, Type type) const
{
	for (list<Entity*>::const_iterator it = childs.begin(); it != childs.cend(); ++it)
	{
		if ((*it)->type == type)
		{
			if (Equals((*it)->name, name))
				return *it;
		}
	}

	return NULL;
}
