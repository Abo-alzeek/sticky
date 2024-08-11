#include "../include/menu.h"

//---------------------------------------------------------------------------------------

Menu::Menu()
{ 
	if (!font.loadFromFile(Resources::getMenuBackgroundFont()))
	{
		std::cout << "Could not load font!" << std::endl;
		return;
	}

	buttonId = 0;
	deltaTime = 0.1f;
	heroSpecSet = false;
	menuState = MAIN_MENU;
}

//---------------------------------------------------------------------------------------

Menu::~Menu()
{
	;
}

//---------------------------------------------------------------------------------------

int Menu::getChosenLevel() {
	return this->chosenLevel;
}

//---------------------------------------------------------------------------------------

std::string Menu::getMainLevel() {
	return this->main_level;
	return "";
}

//--------------------------------------------------------------------------------------

int Menu::getButtonId()
{ 
	return this->buttonId; 
}

//---------------------------------------------------------------------------------------

sf::Font Menu::getFont() 
{ 
	return this->font;
}

//---------------------------------------------------------------------------------------

MenuState Menu::getMenuState()
{ 
	return this->menuState; 
}

//---------------------------------------------------------------------------------------

void Menu::setMenuState(MenuState new_menuState) 
{ 
	this->menuState = new_menuState; 
}

//---------------------------------------------------------------------------------------

void Menu::moveUp()
{
	if (buttonId - 1 >= 0)
	{
		buttons[buttonId]->setColor(sf::Color::White);
		buttonId--;
		buttons[buttonId]->setColor(sf::Color::Red);
	}
}

//---------------------------------------------------------------------------------------

void Menu::moveDown(int maxNumber)
{
	if (buttonId + 1 < maxNumber)
	{
		buttons[buttonId]->setColor(sf::Color::White);
		buttonId++;
		buttons[buttonId]->setColor(sf::Color::Red);
	}
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

MainMenu::MainMenu()
{
	for (int i = 0; i < MAIN_MENU_BUTTONS_QUANTITY; ++i)
	{
		std::shared_ptr<Button> tmp = std::make_shared<Button>();
		tmp->setFont(Menu::font);
		tmp->setColor(sf::Color::White);
		tmp->setSize(100);
		switch (i)
		{
		case 0: tmp->setName("Play"); break;
		case 1: tmp->setName("Options"); break;
		case 2: tmp->setName("Exit"); break;
		default: break;
		}
		tmp->setPos(sf::Vector2f(static_cast<float>(WIDTH - tmp->getText().getGlobalBounds().width) / 2, 
								 static_cast<float>(HEIGHT / (MAIN_MENU_BUTTONS_QUANTITY + 1) + i * 125)));
		buttons.push_back(tmp);
	}

	buttons[0]->setColor(sf::Color::Red);
	backgroundT.loadFromFile(Resources::getMenuBackgroundTexture()); // "Grafiki/map_01.png"
	backgroundS.setTexture(backgroundT);
	backgroundS.setScale(1, 1);
	menuState = MAIN_MENU;
}

//---------------------------------------------------------------------------------------

MainMenu::~MainMenu()
{
	// for (std::vector<std::shared_ptr<Button>>::iterator it = buttons.begin(); it != buttons.end(); ++it)
	// {
	// 	if (*it != nullptr)
	// 		delete (*it);
	// }
}

//---------------------------------------------------------------------------------------

void MainMenu::run(sf::RenderWindow & whichWindow)
{
	// std::cout << "RUNNING MAINMENU...." << std::endl;

	while (whichWindow.isOpen() && this->getMenuState() == MAIN_MENU)
	{
		sf::Event event;

		while (whichWindow.pollEvent(event))
		{
			switch (event.type)	
			{
			case sf::Event::Closed:
			{
				whichWindow.close();
				break;
			}
			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::W:
				case sf::Keyboard::Up:
				{
					this->moveUp();
					break;
				}
				case sf::Keyboard::A:
				case sf::Keyboard::Left:
				{
					break;
				}
				case sf::Keyboard::S:
				case sf::Keyboard::Down:
				{
					this->moveDown(MAIN_MENU_BUTTONS_QUANTITY);
					break;
				}
				case sf::Keyboard::D:
				case sf::Keyboard::Right:
				{
					break;
				}
				case sf::Keyboard::Return:
				{
					switch (this->getButtonId())
					{
					case 0: { 
						std::cout << "Play button has been pressed!" << std::endl; 
						this->setMenuState(MenuState::HOST);
						return; 
					} // menuState = PLAY; 
					case 1: { 
						std::cout << "Options button has been pressed!" << std::endl; 
						break; 
					} // menuState = OPTIONS;
					case 2: { 
						std::cout << "Exit button has been pressed!" << std::endl;
						this->setMenuState(MenuState::EXIT); 
						return; 
					} // menuState = END;
					default: break;
					}
					break;
				}
				case sf::Keyboard::Escape: { 
					std::cout << "Escape has been pressed!" << std::endl; 
					return; 
					break; 
				}
				default: { std::cout << "Unknown key!" << std::endl; break; }
				}
			default:
				break;
			}
			}
		}

		whichWindow.clear();
		this->draw(whichWindow);
		whichWindow.display();
	}
}

//---------------------------------------------------------------------------------------

void MainMenu::draw(sf::RenderWindow & whichWindow)
{
	whichWindow.draw(backgroundS);

	for (int i = 0; i < MAIN_MENU_BUTTONS_QUANTITY; ++i)
	{
		buttons[i]->draw(whichWindow);
	}
}

//---------------------------------------------------------------------------------------

Options::Options()
{
	;
}

//---------------------------------------------------------------------------------------

Options::~Options()
{
	;
}

//---------------------------------------------------------------------------------------

void Options::run(sf::RenderWindow & whichWindow)
{

}

//---------------------------------------------------------------------------------------

void Options::draw(sf::RenderWindow & whichWindow)
{
	;
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

Create::Create() {
	this->chosenLevel = -1;

	std::string current_directory = std::filesystem::current_path();
    std::string path = current_directory + "/res/Levels";

    for (const auto & entry : std::filesystem::directory_iterator(path)) {
		std::string name = entry.path();
		name = name.substr((int)path.size() + 1, (int)name.size() - (int)path.size() - 5);
		levels.push_back( {name, entry.path()} );
	}

	levelName.setPosition(sf::Vector2f(WIDTH - 350, HEIGHT / 2 + 175));
	levelName.setFont(this->font);
	levelName.setCharacterSize(100);

	for (int i = 0; i < HOST_MENU_BUTTONS_QUANTITY; ++i)
	{
		std::shared_ptr<Button> tmp = std::make_shared<Button>();
		tmp->setFont(Menu::font);
		tmp->setColor(sf::Color::White);
		tmp->setSize(100);
		switch (i)
		{
		case 0: tmp->setName("START"); 
			tmp->setPos(sf::Vector2f(static_cast<float>(WIDTH - 330), static_cast<float>(HEIGHT / 2 + 90)));
		break;
		case 1: tmp->setName("<"); 
			tmp->setPos(sf::Vector2f(static_cast<float>(WIDTH - 400), static_cast<float>(HEIGHT / 2 + 175)));
		break;
		case 2: tmp->setName(">"); 
			tmp->setPos(sf::Vector2f(static_cast<float>(WIDTH - 75), static_cast<float>(HEIGHT / 2 + 175)));
		break;
		default: break;
		}

		buttons.push_back(tmp);
	}

	buttons[0]->setColor(sf::Color::Red);
	backgroundT.loadFromFile(Resources::getMenuBackgroundTexture()); 
	backgroundS.setTexture(backgroundT);
	backgroundS.setScale(1, 1);
	levelName.setString(levels[levelsIdx].name);
	menuState = HOST;
}

//---------------------------------------------------------------------------------------

Create::~Create() {

}

//---------------------------------------------------------------------------------------

void Create::run(sf::RenderWindow &whichWindow) {
	while (whichWindow.isOpen() && this->getMenuState() == HOST)
	{
		sf::Event event;

		while (whichWindow.pollEvent(event))
		{
			switch (event.type)	
			{
			case sf::Event::Closed:
			{
				whichWindow.close();
				break;
			}
			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::W:
				case sf::Keyboard::Up:
				{
					this->moveUp();
					break;
				}
				case sf::Keyboard::A:
				case sf::Keyboard::Left:
				{
					buttons[buttonId]->setColor(sf::Color::White);
					this->buttonId = 1;
					buttons[buttonId]->setColor(sf::Color::Red);
					break;
				}
				case sf::Keyboard::S:
				case sf::Keyboard::Down:
				{
					this->moveDown(HOST_MENU_BUTTONS_QUANTITY);
					break;
				}
				case sf::Keyboard::D:
				case sf::Keyboard::Right:
				{
					buttons[buttonId]->setColor(sf::Color::White);
					this->buttonId = 2;
					buttons[buttonId]->setColor(sf::Color::Red);
					break;
				}
				case sf::Keyboard::Return:
				{
					switch (this->getButtonId())
					{
					case 0: { 
						std::cout << "Start button has been pressed!" << std::endl;
						chosenLevel = levelsIdx;
						this->main_level = levels[levelsIdx].path;
						return; 
					}
					case 1: { 
						std::cout << "PREV button has been pressed!" << std::endl; 
						this->showPrevLevel();
						levelName.setString(levels[levelsIdx].name);
						std::cout << "LEVEL: " << levels[levelsIdx].name << std::endl;
						break; 
					} 
					case 2: { 
						std::cout << "NEXT button has been pressed!" << std::endl;
						this->showNextLevel();
						levelName.setString(levels[levelsIdx].name);
						std::cout << "LEVEL: " << levels[levelsIdx].name << std::endl;
						break; 
					} 
					default: break;
					}
					break;
				}
				case sf::Keyboard::Escape: { 
					std::cout << "Escape has been pressed!" << std::endl; 
					this->setMenuState(MenuState::MAIN_MENU);
					return; 
					break; 
				}
				default: { std::cout << "Unknown key!" << std::endl; break; }
				}
			default:
				break;
			}
			}
		}

		if(chosenLevel != -1) {
			this->setMenuState(MAIN_MENU);
		}

		whichWindow.clear();
		this->draw(whichWindow);
		whichWindow.display();
	}
}

//---------------------------------------------------------------------------------------

void Create::showNextLevel() {
	this->levelsIdx = (levelsIdx + 1) % (int)levels.size();
}

//---------------------------------------------------------------------------------------

void Create::showPrevLevel() {
	this->levelsIdx = (levelsIdx - 1 + (int)levels.size()) % (int)levels.size();
}

//---------------------------------------------------------------------------------------

void Create::draw(sf::RenderWindow &whichWindow) {
	whichWindow.draw(backgroundS);

	for (int i = 0; i < HOST_MENU_BUTTONS_QUANTITY; ++i)
	{
		buttons[i]->draw(whichWindow);
	}

	whichWindow.draw(this->levelName);
}

//---------------------------------------------------------------------------------------
