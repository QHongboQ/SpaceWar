#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include <vector>

class GameView {
private:
    sf::Font font;
    sf::Texture heartTexture;
    sf::Texture bulletTexture;

public:
    GameView();
    void drawUI(sf::RenderWindow& window, const Player& player, int score, int level);
    void drawEntities(sf::RenderWindow& window, const std::vector<sf::Sprite>& bullets, const std::vector<sf::Sprite>& enemies, const std::vector<sf::Sprite>& powerUps);

    sf::Texture& getBulletTexture();
};

#endif
