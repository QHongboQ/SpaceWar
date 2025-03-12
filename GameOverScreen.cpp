#include "GameOverScreen.h"

GameOverScreen::GameOverScreen(const sf::Font& font) {
    this->font = font;

    // Set up the main box
    box.setSize(sf::Vector2f(500, 300));
    box.setFillColor(sf::Color(0, 0, 0, 150));
    box.setOutlineThickness(2);
    box.setOutlineColor(sf::Color::White);
    box.setPosition(1381 / 2 - box.getSize().x / 2, 725 / 2 - box.getSize().y / 2);

    // Set up "Game Over" message
    message.setFont(this->font);
    message.setString("Game Over");
    message.setCharacterSize(50);
    message.setFillColor(sf::Color::White);
    message.setPosition(box.getPosition().x + (box.getSize().x - message.getGlobalBounds().width) / 2,
                        box.getPosition().y + 20);

    // Set up Restart button
    restartButton.setFont(this->font);
    restartButton.setString("Restart");
    restartButton.setCharacterSize(30);
    restartButton.setFillColor(sf::Color::White);
    restartButton.setPosition(box.getPosition().x + 50,
                              box.getPosition().y + box.getSize().y - 80);

    restartButtonBox.setSize(sf::Vector2f(restartButton.getGlobalBounds().width + 30,
                                          restartButton.getGlobalBounds().height + 20));
    restartButtonBox.setFillColor(sf::Color(50, 50, 50, 200));
    restartButtonBox.setOutlineThickness(2);
    restartButtonBox.setOutlineColor(sf::Color::White);
    restartButtonBox.setPosition(restartButton.getPosition().x - 10, restartButton.getPosition().y - 5);

    // Set up Main Menu button
    mainMenuButton.setFont(this->font);
    mainMenuButton.setString("Main Menu");
    mainMenuButton.setCharacterSize(30);
    mainMenuButton.setFillColor(sf::Color::White);
    mainMenuButton.setPosition(box.getPosition().x + box.getSize().x - 200,
                               box.getPosition().y + box.getSize().y - 80);

    mainMenuButtonBox.setSize(sf::Vector2f(mainMenuButton.getGlobalBounds().width + 25,
                                           mainMenuButton.getGlobalBounds().height + 20));
    mainMenuButtonBox.setFillColor(sf::Color(50, 50, 50, 200));
    mainMenuButtonBox.setOutlineThickness(2);
    mainMenuButtonBox.setOutlineColor(sf::Color::White);
    mainMenuButtonBox.setPosition(mainMenuButton.getPosition().x - 10, mainMenuButton.getPosition().y - 5);
}

void GameOverScreen::setOnRestart(std::function<void()> callback) {
    onRestart = callback;
}

void GameOverScreen::setOnMainMenu(std::function<void()> callback) {
    onMainMenu = callback;
}

void GameOverScreen::render(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(message);
    window.draw(restartButtonBox);
    window.draw(restartButton);
    window.draw(mainMenuButtonBox);
    window.draw(mainMenuButton);
}

void GameOverScreen::handleInput(const sf::RenderWindow& window, sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        // Check if Restart button is clicked
        if (restartButtonBox.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && onRestart) {
            onRestart(); // Trigger restart callback only on click
        }

        // Check if Main Menu button is clicked
        if (mainMenuButtonBox.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && onMainMenu) {
            onMainMenu(); // Trigger main menu callback only on click
        }
    }
}


bool GameOverScreen::isRestartButtonClicked(const sf::RenderWindow& window) const {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    return restartButtonBox.getGlobalBounds().contains(mousePosition.x, mousePosition.y);
}

bool GameOverScreen::isMainMenuButtonClicked(const sf::RenderWindow& window) const {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    return mainMenuButtonBox.getGlobalBounds().contains(mousePosition.x, mousePosition.y);
}
