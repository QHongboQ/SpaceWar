#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Particle.h"
#include "Player.h"
#include "Enemy.h"
#include "GameOverScreen.h"

class GameScene {
private:
    // Basic game elements
    Player player; // Player object
    int score;                          // Player's score
    int level;                          // Player's level
    
    bool isGameOver;                    // Flag to indicate game over
    std::vector<Enemy> enemies;       // List of enemies

    // Textures and sprites
    sf::Font font;                      // Font for text
    sf::Text scoreText;                 // Text to display score
    sf::Text levelText;                 // Text to display level
    sf::Texture enemyTexture;           // Texture for the enemies
    sf::Texture playerTexture;          // Texture for the player
    sf::Texture heartTexture;           // Texture for the hearts

    // UI elements
    std::vector<Particle> particles; // List of particles
    sf::Sprite hearts[3];               // Array of sprites for the hearts
    std::vector<sf::CircleShape> bullets;   // List of bullets
    
    

    //Enemy enemy; // Enemy object
    
    
    

    // Mechanics of the game
    sf::Clock enemySpawnClock;              // Clock to control enemy spawn rate
    float enemySpawnInterval;              // Interval to spawn enemies
    float bulletSpawnInterval;             // Interval to spawn bullets
    sf::Clock bulletClock;                 // Clock to control bullet generation
    sf::Clock particleClock;               // Clock to control particle generation
    void setupText(sf::Text& text, const std::string& content, float x, float y); // Setup text
    void generateParticle(sf::RenderWindow& window); // Generate a new particle
    void setupHearts(sf::RenderWindow& window); // Setup the hearts
    std::unique_ptr<GameOverScreen> gameOverScreen; // Game over screen

    // Handle player collision with enemies
    void handlePlayerCollision(); // Handle player collision with enemies
    void updateHearts();               // Update hearts based on player's health
    

public:
    GameScene(sf::RenderWindow& window, const sf::Font& font);   // Constructor
    void render(sf::RenderWindow& window); // Render the game scene
    void update(sf::RenderWindow& window); // Update the game scene
    bool isGameOverScreen() const; // Check if the game is over
    void reset(sf::RenderWindow& window, const sf::Font& font);


};

#endif
