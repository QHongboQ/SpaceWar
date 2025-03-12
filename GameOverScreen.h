#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include <SFML/Graphics.hpp>
#include <string>
#include <functional> // For std::function

class GameOverScreen {
private:
    sf::RectangleShape box;                // Main box for the Game Over screen
    sf::Text message;                      // "Game Over" message

    sf::Text restartButton;                // "Restart" button text
    sf::Text mainMenuButton;               // "Main Menu" button text

    sf::RectangleShape restartButtonBox;   // Box for "Restart" button
    sf::RectangleShape mainMenuButtonBox;  // Box for "Main Menu" button

    // Callback functions for button actions
    std::function<void()> onRestart;
    std::function<void()> onMainMenu;

    sf::Font font;                         // Font for text

public:
    GameOverScreen(const sf::Font& font);  // Constructor to initialize the screen

    void render(sf::RenderWindow& window); // Render the Game Over screen
    void handleInput(const sf::RenderWindow& window, sf::Event event);

    void setOnRestart(std::function<void()> callback);
    void setOnMainMenu(std::function<void()> callback);

    bool isRestartButtonClicked(const sf::RenderWindow& window) const;
    bool isMainMenuButtonClicked(const sf::RenderWindow& window) const;

    
};

#endif // GAMEOVERSCREEN_H
