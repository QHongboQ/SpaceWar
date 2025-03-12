#include "Player.h"
#include <stdexcept>

Player::Player(const std::string& textureFile, float vel, int hp, int bulletPattern)
    : velocity(vel), health(hp), bulletPattern(bulletPattern) {
    if (!texture.loadFromFile(textureFile)) {
        throw std::runtime_error("Failed to load player texture: " + textureFile);
    }
    sprite.setRotation(180.f); // Rotate the player sprite by 180 degrees
    sprite.setTexture(texture);
    sprite.setScale(0.1f, 0.1f);
    
    // Calculate the initial position: Bottom center of the screen
    float windowWidth = 1381.f; // Window width
    float windowHeight = 725.f; // Window height
    float playerWidth = sprite.getGlobalBounds().width;
    float playerHeight = sprite.getGlobalBounds().height;

    float startX = (windowWidth - playerWidth) / 2; // Center horizontally
    float startY = windowHeight - playerHeight - 20; // Slightly above the bottom (20px padding)

    sprite.setPosition(startX, startY); // Set the initial position
}

void Player::move(const sf::RenderWindow& window) {
    sf::Vector2f movement(0.f, 0.f);

    // Handle keyboard input for movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y -= velocity;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += velocity;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movement.x -= velocity;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += velocity;
    }

    // Keep the player within the screen bounds
    sf::Vector2f newPosition = sprite.getPosition() + movement;
    if (newPosition.x >= 50 && newPosition.x + sprite.getGlobalBounds().width <= 1381+150 &&
        newPosition.y >= 150 && newPosition.y + sprite.getGlobalBounds().height <= 725+150) {
        sprite.move(movement);
    }

}

std::vector<sf::Sprite> Player::shoot(sf::Texture& bulletTexture) {
    std::vector<sf::Sprite> bullets;

    // Create bullets based on the current bullet pattern
    sf::Sprite bullet;
    bullet.setTexture(bulletTexture);
    bullet.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width / 2 - bullet.getGlobalBounds().width / 2,
                       sprite.getPosition().y - bullet.getGlobalBounds().height);
    bullets.push_back(bullet);

    // Add additional bullets for different patterns
    if (bulletPattern > 1) {
        bullet.setPosition(sprite.getPosition().x, sprite.getPosition().y - bullet.getGlobalBounds().height);
        bullets.push_back(bullet);

        bullet.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width - bullet.getGlobalBounds().width,
                           sprite.getPosition().y - bullet.getGlobalBounds().height);
        bullets.push_back(bullet);
    }

    return bullets;
}

int Player::getHealth() const {
    return health;
}

sf::Sprite& Player::getSprite() {
    return sprite;
}

void Player::eventHandler(const sf::RenderWindow& window) {
    move(window);
}

std::vector<sf::CircleShape> Player::fire() {
    std::vector<sf::CircleShape> bullets;

    // Create a bullet
    sf::CircleShape bullet;
    bullet.setRadius(5.f);  // Set the radius of the bullet
    bullet.setScale(1.5f, 0.5f);    // Scale the bullet to make it look like a rectangle
    bullet.setFillColor(sf::Color::Yellow);     // Set the color of the bullet

    bullet.setOrigin(bullet.getRadius(), bullet.getRadius()); // Set the origin to the center of the bullet
    bullet.setRotation(90.f);   // Rotate the bullet to face upwards

    // Set the position of the bullet to the center of the player sprite
    bullet.setPosition(
        sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2 - bullet.getRadius(),
        sprite.getGlobalBounds().top - bullet.getRadius()
    );
    bullets.push_back(bullet);

    return bullets;
}

void Player::takeDamage() {
    if (health > 0) {
        health--; // Decrease health by 1
    }
}
