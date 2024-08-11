#include "../include/game.h"

//---------------------------------------------------------------------------------------

Game::Game()
{
	window.create(sf::VideoMode(WIDTH, HEIGHT), "Stickman Game", sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	state = GameState::MENU;
}

//---------------------------------------------------------------------------------------

Game::~Game()
{
	std::cout << "End of Game, thanks for playing!" << std::endl;
}

//---------------------------------------------------------------------------------------

sf::RenderWindow & Game::getWindow()
{
	return window;
}

//---------------------------------------------------------------------------------------

GameState Game::getState()
{
	return state;
}

//---------------------------------------------------------------------------------------

void Game::setState(GameState state_)
{
	this->state = state_;
}

//---------------------------------------------------------------------------------------

void Game::run()
{
	std::shared_ptr<Menu> menu_ptr = nullptr;
	MainMenu mainMenu;
	menu_ptr = std::make_shared<MainMenu>(mainMenu);

	// -------- GAMESTATE -----------
	while (state != END)
	{
		switch (this->state)
		{
			case GameState::MENU:
			{
				// -------- MENUSTATE -----------
				while (menu_ptr->getMenuState() != OUT)
				{
					switch (menu_ptr->getMenuState())
					{
					case MenuState::MAIN_MENU:
					{
						menu_ptr = std::make_shared<MainMenu>(mainMenu);
						menu_ptr->setMenuState(MenuState::MAIN_MENU);
						menu_ptr->run(this->Game::getWindow());
						break;
					}
					case MenuState::HOST:
					{
						std::shared_ptr<Create> create = std::make_shared<Create>();
						menu_ptr = create;
						menu_ptr->setMenuState(MenuState::HOST);
						menu_ptr->run(this->Game::getWindow());

						if(menu_ptr->getChosenLevel() != -1) {
							this->level = menu_ptr->getMainLevel();							
							this->state = GameState::GAME;
							menu_ptr->setMenuState(MenuState::OUT);
						}
					}
					case MenuState::OPTIONS:
					{
						//Options * options = new Options;
						//menu_ptr = &options;
						//menu_ptr->setMenuState(OPTIONS);
						break;
					}
					case MenuState::GAME_OVER:
					{
						break;
					}
					case MenuState::EXIT:
					{
						menu_ptr->setMenuState(MenuState::OUT);
						this->state = GameState::END;
						break;
					}
					default:
						std::cout << "MENU NOT FOUND!!" << std::endl;
						break;
					}
				}

				 break;
			}

			// -------- TRYB GRY -----------
			case GameState::GAME: 
			{
				std::cout << "Starting game on level: " << this->level << std::endl;

				std::shared_ptr<Engine> engine = std::make_shared<Engine>(this->level);
				engine->run(this->getWindow());
				std::cout << "DONE RUNNING!" << std::endl;
				this->state = GameState::END;
				menu_ptr->setMenuState(MenuState::GAME_OVER);
				break;
			}

			//  --------- TRYB WYJSCIA --------
			case GameState::END: 
			{
				std::cout << "End of game!" << std::endl;
				break;
			}

			default:
				break;
		}
	}
}

//---------------------------------------------------------------------------------------

void Game::updateScore(int points_, float time_)
{
	this->lastPoints = points_;
	this->lastTime = time_;
}

//---------------------------------------------------------------------------------------