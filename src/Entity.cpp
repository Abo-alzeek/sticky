#include "../include/basic.h"

Entity::Entity() {
	cInput = NULL;
	cTextrue = NULL;
	cCollision = NULL;
	cAnimation = NULL;
	cTransform = NULL;
	// zob = NULL;
}

Entity::~Entity() {
	cInput = NULL;
	cTextrue = NULL;
	cCollision = NULL;
	cAnimation = NULL;
	cTransform = NULL;
	// zob = NULL;
}


Entity::Entity(const size_t id, const std::string *tag) {
	m_id = id;
	m_tag = *tag;
}

void Entity::destroy(){
	m_alive = false;
}

bool Entity::isActive() const {
	return m_alive;
}

const std::string &Entity::tag() const {
	return m_tag;
}

const size_t Entity::id() const {
	return m_id;
}