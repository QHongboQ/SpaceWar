#include "GameController.h"


GameController::GameController(GameView& view) 
    : view(view), 
      player("Player.png", 0.05f, 3, 1), 
      score(0), 
      level(1) {}

void GameController::handleInput(sf::RenderWindow& window) {
    player.move(window);


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

        auto newBullets = player.shoot(view.getBulletTexture());


        bullets.insert(bullets.end(), newBullets.begin(), newBullets.end());
    }
}
