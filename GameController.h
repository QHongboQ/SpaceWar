#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "GameView.h"

class GameController {
private:
    Player player; 
    std::vector<sf::Sprite> bullets; 
    GameView& view; 
    int score;
    int level;

public:
    GameController(GameView& view); 
    void handleInput(sf::RenderWindow& window);
};

#endif