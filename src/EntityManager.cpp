#include "../include/basic.h"

EntityManager::EntityManager() {
	;
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string *tag) {
	auto e = std::make_shared<Entity>(this->m_totalEntities++, tag);
	m_toAdd.push_back(e);
	return e;
}

void EntityManager::update() {
	for(auto e : this->m_toAdd) {
		m_entities.push_back(e);
		m_entityMap[e->tag()].push_back(e);
	}

	for(int i = 0;i < (int)m_entities.size();i++) {
		if(!m_entities[i]->isActive()) {
			swap(m_entities[i], m_entities.back());
			m_entities.pop_back();
			i--;
			if(!(int)m_entities.size()) break;
		}
	}

	for(auto &element : this->m_entityMap) {
		for(int i = 0;i < (int)element.second.size();i++) {
			if(!element.second[i]->isActive()) {
				swap(element.second[i], element.second.back());
				element.second.pop_back();
				i--;
				if(!(int)element.second.size()) break;
			}
		}
	}

	this->m_toAdd.clear();
}

EntityVec& EntityManager::getEntities() {
	return this->m_entities;
}

EntityVec& EntityManager::getEntities(const std::string &tag) {
	return this->m_entityMap[tag];
}