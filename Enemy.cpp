#include "Enemy.h"

Enemy::Enemy(const sf::Texture& sharedTexture, float speed) : texture(&sharedTexture), speed(speed) {
    sprite.setTexture(*texture); // Set the texture

    sprite.setScale(0.15f, 0.25f);

    sprite.setRotation(270.0f);
    
    // Randomize initial position
    float x = static_cast<float>(rand() % 1381); // Assuming window width is 1381
    sprite.setPosition(x, -sprite.getGlobalBounds().height); // Spawn at top of the screen
}

void Enemy::update() {
    sprite.move(0.f, speed); // Move enemy downward
}

void Enemy::render(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect Enemy::getBounds() const {
    return sprite.getGlobalBounds();
}
