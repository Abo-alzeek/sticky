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
	std::shared_ptr<CInput>          cInput = nullptr;
	std::shared_ptr<CTexture>        cTextrue = nullptr;
	std::shared_ptr<CCollision>  	 cCollision = nullptr;
	std::shared_ptr<CAnimation>      cAnimation = nullptr;
	std::shared_ptr<CTransform>      cTransform = nullptr;
	std::shared_ptr<CBones>          cBones = nullptr;
	std::shared_ptr<CState>          cState = nullptr;
	
	void destroy();
	bool isActive() const;
	const std::string &tag() const;
	const size_t id() const;
};

#endif
