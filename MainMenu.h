#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class MainMenu {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Font font;
    sf::Text beginNewGameButton;
    sf::Text exitButton;

    sf::RectangleShape beginNewGameBox;
    sf::RectangleShape exitBox;

    void setupButton(sf::Text& button, sf::RectangleShape& box, const std::string& text, float x, float y);

public:
    MainMenu(); // Constructor to initialize the menu
    int display(sf::RenderWindow& window); // Display the menu and return user choice
};

#endif
