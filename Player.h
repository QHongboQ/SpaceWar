#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>

class Player {
private:
    sf::Sprite sprite;         // Player's sprite
    sf::Texture texture;       // Player's texture
    int health;                // Player's health
    int bulletPattern;         // Bullet firing pattern
    float velocity;            // Movement speed

public:
    Player(const std::string& textureFile, float vel, int hp, int bulletPattern);
    void move(const sf::RenderWindow& window);
    std::vector<sf::CircleShape> fire();    // Fire bullets
    std::vector<sf::Sprite> shoot(sf::Texture& bulletTexture);
    void takeDamage();
    int getHealth() const;
    sf::Sprite& getSprite();
    void eventHandler(const sf::RenderWindow& window); // Handles player movement based on input
};

#endif
