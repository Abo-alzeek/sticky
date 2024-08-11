#ifndef ENGINE_H_
#define ENGINE_H_

#define WAIT_TIME 5
#include "basic.h"

class Engine
{
	bool running = true; 
	int m_currentFrame = 0;
	EntityManager    m_entities;
	Resources        m_resources;

	Level level;
    std::vector< std::vector<sf::Sprite> > MapSprites;

	std::string tileTag = "TILE";
	std::string stickmanTag = "STICKMAN";
	std::string skeletalTag = "SKELETALTAG";
public:
	Engine(std::string);
	~Engine();

	void handleInput(sf::RenderWindow &);
	void update();
	void checkCollisions();
	void render(sf::RenderWindow &);

	void run(sf::RenderWindow &); 
};

#endif