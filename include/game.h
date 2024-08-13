#ifndef GAME_H_
#define GAME_H_

#include "basic.h"

enum GameState { MENU = 0, GAME = 1, END = 2};

class Game
{
protected:
	static sf::RenderWindow window; 
	GameState state; 
	int lastPoints; 
	float lastTime;
	std::string level;

public:
	Game();
	~Game();

	static sf::RenderWindow & getWindow();
	GameState getState(); 
	void setState(GameState); 

	void run(); 
	void updateScore(int, float); 
};

#endif
