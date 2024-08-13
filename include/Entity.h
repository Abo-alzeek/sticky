#ifndef ENTITY_H_
#define ENTITY_H_

#include "basic.h"

class Entity {
	size_t m_id = 0;
	bool m_alive = true;
	std::string m_tag = "Default";

public:
	Entity();
	~Entity();
	Entity(const size_t id, const std::string *tag);
	std::shared_ptr<CInput>          						cInput;
	std::shared_ptr<CTexture>        						cTextrue;
	std::vector<std::shared_ptr<CCollision>>    cCollision;
	std::shared_ptr<CAnimation>									cAnimation;
	std::shared_ptr<CTransform>									cTransform;
	std::shared_ptr<CBones>          						cBones;
	std::shared_ptr<CState>          						cState;
	std::shared_ptr<CHealth>                    cHealth;
	
	void destroy();
	bool isActive() const;
	const std::string &tag() const;
	const size_t id() const;
};

#endif
