#include "Entity.h"

Entity::Entity(size_t id, const std::string& tag) : _id(id), _tag(tag) {}

const std::string Entity::tag() const
{
	return _tag;
}

const size_t Entity::id() const
{
	return _id;
}

bool Entity::getStatus()
{
	return _alive;
}

void Entity::destroy() {
	_alive = false;
}
