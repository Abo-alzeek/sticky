#ifndef MENU_H_
#define MENU_H_

#include "basic.h"

#define MAIN_MENU_BUTTONS_QUANTITY 3
#define PLAY_BUTTONS_QUANTITY 5
#define OPTIONS_BUTTONS_QUANTITY 5
#define NEXT_LEVEL_BUTTONS_QUANTITY 2
#define GAMEOVER_BUTTONS_QUANTITY 1
#define ENDGAME_BUTTONS_QUANTITY 4
#define HOST_MENU_BUTTONS_QUANTITY 3

enum MenuState { MAIN_MENU = 0, PLAY = 1, OPTIONS = 2, EXIT = 3, NEXT = 4, GAME_OVER = 5, OUT = 6, HOST = 7, JOIN = 8};

class Menu
{
protected:
	int buttonId; 
	float deltaTime; 
	bool heroSpecSet; 
	int chosenLevel;
	std::string main_level;
	
	std::vector<std::shared_ptr<Button>> buttons; 
	sf::Texture backgroundT; 
	sf::Sprite backgroundS; 
	sf::Font font;
	
	MenuState menuState; 
public:
	Menu();
	virtual ~Menu();

	int getChosenLevel();
	std::string getMainLevel();

	int getButtonId(); 
	sf::Font getFont(); 
	MenuState getMenuState(); 
	
	void setMenuState(MenuState); 

	virtual void moveUp(); 
	virtual void moveDown(int); 
	
	virtual void run(sf::RenderWindow &) = 0; 
	virtual void draw(sf::RenderWindow &) = 0; 
};

//---------------------------------------------------------------------------------------

class MainMenu : public Menu
{
public:
	MainMenu();
	~MainMenu();

	virtual void run(sf::RenderWindow &) final; // Rozpoczyna dzia�anie menu
	virtual void draw(sf::RenderWindow &) final; // Rysuje menu
};

//---------------------------------------------------------------------------------------

class Options : public Menu
{
public:
	Options();
	~Options();

	virtual void run(sf::RenderWindow &) final;
	virtual void draw(sf::RenderWindow &) final;
};

//---------------------------------------------------------------------------------------

class Create : public Menu 
{
	int levelsIdx = 0;
	std::vector< miniLevel > levels;
	sf::Text levelName;
public:
	Create();
	~Create();

	void showNextLevel();
	void showPrevLevel();
	virtual void run(sf::RenderWindow &) final;
	virtual void draw(sf::RenderWindow &) final;
};

//---------------------------------------------------------------------------------------

#endif