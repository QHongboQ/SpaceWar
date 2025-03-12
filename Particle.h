#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>

class Particle {
private:
    sf::RectangleShape shape;
    float speed; // Vertical movement speed

public:
    Particle(float x, float y, float width, float height, sf::Color color, float speed);
    void update(); // Update the particle's position
    void render(sf::RenderWindow& window) const; // Draw the particle (add const here)
    bool isOffScreen(float windowHeight) const; // Check if particle is out of screen
};

#endif
