#include "MainMenu.h"
#include <stdexcept>

MainMenu::MainMenu() {
    // Load background texture
    if (!backgroundTexture.loadFromFile("Background.jpg")) {
        throw std::runtime_error("Failed to load Background.jpg");
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Load font
    if (!font.loadFromFile("OpenSans-Bold.ttf")) {
        throw std::runtime_error("Failed to load OpenSans-Bold.ttf");
    }

    // Set up buttons with their boxes
    setupButton(beginNewGameButton, beginNewGameBox, "Begin New Game", 300, 500); // Leftmost button
    setupButton(exitButton, exitBox, "Exit", 900, 500); // Rightmost button
}

void MainMenu::setupButton(sf::Text& button, sf::RectangleShape& box, const std::string& text, float x, float y) {
    // Set up the button text
    button.setFont(font);
    button.setString(text);
    button.setCharacterSize(30); // Font size for the button
    button.setFillColor(sf::Color::White);
    button.setPosition(x, y);

    // Set up the surrounding box
    sf::FloatRect textBounds = button.getGlobalBounds();
    box.setSize(sf::Vector2f(textBounds.width + 20, textBounds.height + 10)); // Add padding
    box.setFillColor(sf::Color(0, 0, 0, 150)); // Semi-transparent black background
    box.setOutlineThickness(2);
    box.setOutlineColor(sf::Color::White); // White border
    box.setPosition(textBounds.left - 10, textBounds.top - 5); // Align box with text
}

int MainMenu::display(sf::RenderWindow& window) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1; // Exit game
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                if (beginNewGameBox.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                    return 0; // Begin new game
                }
            
                if (exitBox.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                    window.close();
                    return -1; // Exit game
                }
            }
        }

        // Draw the menu
        window.clear();
        window.draw(backgroundSprite);
        window.draw(beginNewGameBox);
        window.draw(beginNewGameButton);
        window.draw(exitBox);
        window.draw(exitButton);
        window.display();
    }
    return -1;
}
