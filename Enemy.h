#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
private:
    sf::Sprite sprite;               // Sprite for the enemy
    const sf::Texture* texture;      // Texture for the enemy
    float speed;                     // Speed of the enemy
public:
    Enemy(const sf::Texture& sharedTexture, float speed);
    void update();
    void render(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
};

#endif
