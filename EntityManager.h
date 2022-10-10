#pragma once



#include <vector>
#include <string>
#include <map>
#include <memory>


#include "Entity.h"

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;

class EntityManager
{
	EntityVec _entities;										 // all entities
	EntityMap _entityMap;										 // grouping entites by their tag
	EntityVec _toAdd;											 // entities to be added to _entities after next frame
	size_t    _totalEntites = 0;								 // number of entities created

	void removeDeadEntities(EntityVec& vec);

public:
	EntityManager() = default;
	
	void update();
	
	std::shared_ptr<Entity> addEntity(const std::string& tag);   // create new entity and return it
	
	const EntityVec& getEntities();									 // return all the entities
	const EntityVec& getEntities(const std::string& tag);				 // return a specific entity by tag
};