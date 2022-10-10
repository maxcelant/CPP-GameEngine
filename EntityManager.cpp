

#include <vector>
#include <string>
#include <map>
#include <memory>

#include "EntityManager.h"
#include "Entity.h"

void EntityManager::removeDeadEntities(EntityVec & vec)
{
	std::remove_if(vec.begin(), vec.end(), [](auto e) { return !e->getStatus(); }); //! Keep an eye on this
}

// called at beginning of each fram by game engine
// entities added will now be available to use this frame
void EntityManager::update()
{
	for (auto e : _toAdd)
	{
		_entities.push_back(e);								     // add to full entity list
		_entityMap[e->tag()].push_back(e);						 // add to correct entity group
	}

	_toAdd.clear();												// clear the waiting room now that they've all been added

	removeDeadEntities(_entities);

	for (auto& kv : _entityMap) // TODO: figure this out
	{
		removeDeadEntities(kv.second);
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

