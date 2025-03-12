#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "GameScene.h"

int main() {
    // Create the main application window with updated size
    sf::RenderWindow window(sf::VideoMode(1381, 725), "Space War");
    window.setFramerateLimit(60);

    // Load the font to be shared across scenes
    sf::Font sharedFont;
    if (!sharedFont.loadFromFile("OpenSans-Bold.ttf")) {
        // Handle the error if the font cannot be loaded
        return -1;
    }

    // Track the current scene
    enum Scene { MENU, GAME, GAME_OVER, EXIT } currentScene = MENU;

    // Declare GameScene outside the loop for wider scope, but initialize when needed
    GameScene* gameScene = nullptr;

    while (window.isOpen()) {
        if (currentScene == MENU) {
            MainMenu mainMenu;
            int result = mainMenu.display(window);
            if (result == 0) {
                // Create a new instance of GameScene when starting a new game
                if (gameScene) delete gameScene;
                gameScene = new GameScene(window, sharedFont); // Pass the shared font
                currentScene = GAME;
            } else if (result == -1) {
                currentScene = EXIT; // Exit the program
            }
        } else if (currentScene == GAME) {
            while (currentScene == GAME) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        currentScene = EXIT;
                    }
                }

                // Update the game scene
                gameScene->update(window);

                // Check if game is over
                if (gameScene->isGameOverScreen()) {
                    currentScene = GAME_OVER;
                }

                // Render the game scene
                window.clear();
                gameScene->render(window);
                window.display();
            }
        } else if (currentScene == GAME_OVER) {
            GameOverScreen gameOverScreen(sharedFont); // Pass the shared font
            bool done = false;
            while (!done) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        currentScene = EXIT;
                        done = true;
                    }

                    gameOverScreen.handleInput(window, event);
                }

                // Only proceed if a mouse button is pressed
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (gameOverScreen.isRestartButtonClicked(window)) {
                    currentScene = GAME; // Restart the game
                    // Create a new instance of GameScene when restarting
                    if (gameScene) delete gameScene;
                    gameScene = new GameScene(window, sharedFont); // Pass the shared font
                    done = true;
                } else if (gameOverScreen.isMainMenuButtonClicked(window)) {
                    currentScene = MENU; // Go back to main menu
                    done = true;
                }
                }

                // Render game over screen
                window.clear();
                gameOverScreen.render(window);
                window.display();
            }
        } else if (currentScene == EXIT) {
            window.close(); // Exit the program
        }
    }

    // Clean up dynamically allocated memory
    if (gameScene) delete gameScene;

    return 0;
}
