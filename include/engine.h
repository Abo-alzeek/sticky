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
	sf::Vector2f skeletonBoundingBoxes[3] = {sf::Vector2f(30, 30), sf::Vector2f(40, 80), sf::Vector2f(35, 35)};
	float skeletonBoundingBoxesMargins[3] = {-skeletonBoundingBoxes[0].y / 2 - skeletonBoundingBoxes[1].y / 2 - 10, 0.0, skeletonBoundingBoxes[1].y / 2 + skeletonBoundingBoxes[2].y / 2 + 10};
	sf::Color skeletonBoxesColors[3] = {sf::Color::Blue, sf::Color::Red, sf::Color::Yellow};
public : Engine(std::string);
	~Engine();

  void createSkeletonBoundingBoxes(std::shared_ptr<Entity>);
	void handleInput(sf::RenderWindow &);
	void update();
	void checkCollisions();
	void render(sf::RenderWindow &);

	void run(sf::RenderWindow &);
};

#endif