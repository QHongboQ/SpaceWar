#include "Particle.h"

Particle::Particle(float x, float y, float width, float height, sf::Color color, float speed)
    : speed(speed) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(color);
    shape.setPosition(x, y);
}

void Particle::update() {
    // Move the particle downward
    shape.move(0, speed);
}

void Particle::render(sf::RenderWindow& window) const {
    window.draw(shape); // No changes required here, just ensure the function is marked const
}

bool Particle::isOffScreen(float windowHeight) const {
    return shape.getPosition().y > windowHeight;
}
