

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <algorithm>
#include <iostream>

#include "EntityManager.h"
#include "Entity.h"

void EntityManager::removeDeadEntities(EntityVec & vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (!vec[i]->getStatus())
		{
			vec.erase(vec.begin() + i);
		}
	}
}

// called at beginning of each fram by game engine
// entities added will now be available to use this frame
void EntityManager::update()
{
	for (auto e : _toAdd)
	{
		_entities.push_back(e);								     // add to full entity list
		_entityMap[e->tag()].push_back(e);						 // add to correct entity group
		std::cout << "Entity created" << std::endl;
	}

	_toAdd.clear();												// clear the waiting room now that they've all been added

	removeDeadEntities(_entities);

	for (auto& [tag, entities]:_entityMap)
	{
		removeDeadEntities(entities);
	}
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	auto e = std::shared_ptr<Entity>(new Entity(_totalEntites++, tag));    // create a new entity with an id
	_toAdd.push_back(e);													// add to waiting room list
	return e;
}

const EntityVec& EntityManager::getEntities()
{
	return _entities;
}

const EntityVec& EntityManager::getEntities(const std::string& tag)
{
	return _entityMap[tag];
}

