#pragma once

#include "Components.h"
#include <string>
#include <memory>

class Entity
{
	friend class EntityManager;

	const size_t	  _id = 0;
	const std::string _tag = "Default";
	bool			  _alive = true;

	Entity(size_t id, const std::string& tag);

public:
	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<CShape>     cShape;
	std::shared_ptr<CCollision> cCollision;
	std::shared_ptr<CInput>     cInput;
	std::shared_ptr<CScore>		cScore;
	std::shared_ptr<CLifespan>  cLifespan;
	
	const std::string tag() const;		// return the tag of the entity
	const size_t id() const;			// return the id of the entity
	bool getStatus();					// return the _alive status
	void destroy();						// turns _alive to false
};
