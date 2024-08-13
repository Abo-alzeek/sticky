#ifndef ENGINE_H_
#define ENGINE_H_

#define WAIT_TIME 5
#include "basic.h"

class Engine
{
	bool running = true;
	int m_currentFrame = 0;
	EntityManager m_entities;
	Resources m_resources;

	Level level;
	std::vector<std::vector<sf::Sprite>> MapSprites;

	std::string tileTag = "TILE";
	std::string stickmanTag = "STICKMAN";
	std::string skeletalTag = "SKELETALTAG";

	sf::Vector2f skeletonBoundingBoxes[3] = {sf::Vector2f(40, 40), sf::Vector2f(40, 100), sf::Vector2f(40, 43)};
	float skeletonBoundingBoxesMargins[3] = {-skeletonBoundingBoxes[0].y / 2 - skeletonBoundingBoxes[1].y / 2, 0.0, skeletonBoundingBoxes[1].y / 2 + skeletonBoundingBoxes[2].y / 2};
	sf::Color skeletonBoxesColors[3] = {sf::Color(255, 0, 0, 255), sf::Color(0, 255, 0, 255), sf::Color(0, 255, 255, 255)};

public : Engine(std::string);
	~Engine();

	void moveAll(std::shared_ptr<Entity> , sf::Vector2f);
	void createSkeletonBoundingBoxes(std::shared_ptr<Entity>);
	void handleInput(sf::RenderWindow &);
	void update();
	void checkCollisions(sf::RenderWindow &);
	void render(sf::RenderWindow &);
	void spawnStickman(bool, bool, bool, bool, bool, bool, bool, bool, int);

	void run(sf::RenderWindow &);
};

#endif