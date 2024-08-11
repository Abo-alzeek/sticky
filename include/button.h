#ifndef BUTTON_H_
#define BUTTON_H_

class Button
{
	sf::Text text; // Biblioteczna zmienna pozwalaj�ca na modyfikacj� wy�wietlanego tekstu

public:
	Button();
	Button(int, const std::string &);
	~Button();

	sf::Text getText() { return text; } // Metoda pobieraj�ca aktualny tekst przycisku

	void setPos(const sf::Vector2f &); // Metoda ustawiaj�ca pozycj� przycisku na ekranie
	void setColor(sf::Color); // Metoda ustawiaj�ca kolor tekstu w przycisku
	void setName(const std::string &); // Metoda ustawiaj�ca nazw� przycisku
	void setFont(const sf::Font &); // Metoda ustawiaj�ca czcionk� tekstowi przycisku
	void setSize(const int); // Metoda ustawiaj�ca wielko�� tekstu przycisku
	void handleEvents(sf::Vector2f &); // Metoda okre�laj�ca jak przycisk ma si� zachowywa� w interakcji
	void draw(sf::RenderWindow &); // Metoda wy�wietlaj�ca przycisk
};

#endif