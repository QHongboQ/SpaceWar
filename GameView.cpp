#include "GameView.h"

GameView::GameView() {
    font.loadFromFile("font.ttf");
    heartTexture.loadFromFile("heart.png");
    bulletTexture.loadFromFile("bullet.png");
}

void GameView::drawUI(sf::RenderWindow& window, const Player& player, int score, int level) {
    for (int i = 0; i < player.getHealth(); ++i) {
        sf::Sprite heart(heartTexture);
        heart.setPosition(700 + i * 30, 10);
        window.draw(heart);
    }

    sf::Text scoreText("Score: " + std::to_string(score), font, 20);
    sf::Text levelText("Level: " + std::to_string(level), font, 20);
    scoreText.setPosition(10, 10);
    levelText.setPosition(10, 40);

    window.draw(scoreText);
    window.draw(levelText);
}

void GameView::drawEntities(sf::RenderWindow& window, const std::vector<sf::Sprite>& bullets, const std::vector<sf::Sprite>& enemies, const std::vector<sf::Sprite>& powerUps) {
    for (const auto& bullet : bullets)
        window.draw(bullet);

    for (const auto& enemy : enemies)
        window.draw(enemy);

    for (const auto& powerUp : powerUps)
        window.draw(powerUp);
}

sf::Texture& GameView::getBulletTexture() {
    return bulletTexture;
}

