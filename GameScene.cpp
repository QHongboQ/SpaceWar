#include "GameScene.h"
#include <stdexcept>
#include <random>
#include <chrono> // For time-based seed
#include <iostream> // For debugging

GameScene::GameScene(sf::RenderWindow& window, const sf::Font& font) 
    : player("Player.png", 7.5f, 3, 1), // Player texture, velocity, health, bullet pattern
      score(0), 
      level(1), 
      isGameOver(false),
      font(font),
      enemySpawnInterval(2.0f),
      bulletSpawnInterval(0.5f) {

    // Load Enemy texture
    if (!enemyTexture.loadFromFile("Enemy.png")) {
        throw std::runtime_error("Failed to load Enemy.png");
    }

    // Load heart texture
    if (!heartTexture.loadFromFile("HP.png")) {
        throw std::runtime_error("Failed to load HP.png");
    }

    // Setup UI elements
    setupHearts(window);
    setupText(scoreText, "Score: 0", 10.f, 10.f);
    setupText(levelText, "Level: 1", 10.f, 50.f);

    // Initialize game over screen
    gameOverScreen = std::make_unique<GameOverScreen>(font);
    gameOverScreen->setOnRestart([this, &window, font]() {
        *this = GameScene(window, font); // Restart the game with shared font
    });

    gameOverScreen->setOnMainMenu([this]() {
        isGameOver = false; // Notify to switch to main menu
    });
}

void GameScene::reset(sf::RenderWindow& window, const sf::Font& font) {
    score = 0;
    level = 1;
    enemySpawnInterval = 2.0f;
    bulletSpawnInterval = 0.5f;
    isGameOver = false;
    bullets.clear();
    enemies.clear();
    particles.clear();
    player = Player("Player.png", 7.5f, 3, 1);
    setupHearts(window);
    setupText(scoreText, "Score: 0", 10.f, 10.f);
    setupText(levelText, "Level: 1", 10.f, 50.f);
}




void GameScene::render(sf::RenderWindow& window) {
    // Check if the game is over
    if (isGameOver) {
        gameOverScreen->render(window);
        return;
    }

    // Draw particles
    for (const auto& particle : particles) {
        particle.render(window);
    }
    
    // Draw enemies
    for (const auto& enemy : enemies) {
        enemy.render(window);
    }

    // Draw player
    window.draw(player.getSprite());

    // Draw bullets
    for (const auto& bullet : bullets) {
        window.draw(bullet);
    }

    // Draw the hearts
    for (int i = 0; i < 3; ++i) {
        window.draw(hearts[i]);
    }

    // Draw the score and level
    window.draw(scoreText);
    window.draw(levelText);

}




void GameScene::update(sf::RenderWindow& window) {
    if (isGameOver) {
        sf::Event event;
        while (window.pollEvent(event)) {
            gameOverScreen->handleInput(window, event);
        }
        return;
    }

    // Debug output to track game state
    std::cout << "Score: " << score << " | Level: " << level 
              << " | Enemy Spawn Interval: " << enemySpawnInterval 
              << "s | Bullet Spawn Interval: " << bulletSpawnInterval << "s" << std::endl;



    // Handle player input
    player.move(window);

    // Update level based on score
    int newLevel = score / 10 + 1;
    if (newLevel > level) {
        level = newLevel;
        levelText.setString("Level: " + std::to_string(level));
        
        // Decrease enemy spawn interval and bullet spawn interval
        enemySpawnInterval = std::max(0.1f, enemySpawnInterval - 0.5f);
        bulletSpawnInterval = std::max(0.05f, bulletSpawnInterval - 0.1f);
    }


    // Generate particles less frequently
    if (particleClock.getElapsedTime().asMilliseconds() > 300) { // Every 300ms
        generateParticle(window);
        particleClock.restart();
    }

    // Generate bullets
    if (bulletClock.getElapsedTime().asSeconds() >= bulletSpawnInterval) { // Update bullet spawn interval
        auto newBullets = player.fire(); // Fire bullets
        bullets.insert(bullets.end(), newBullets.begin(), newBullets.end());
        bulletClock.restart();
    }

    // Draw all particles
    for (auto& particle : particles) {
        particle.update();
    }

    // Remove particles that are off-screen
    particles.erase(std::remove_if(particles.begin(), particles.end(),[&](const Particle& p) 
    {
    return p.isOffScreen(static_cast<float>(window.getSize().y));
    }),
    particles.end());

    // Draw bullets
    for (auto it = bullets.begin(); it != bullets.end();) {
        it->move(0, -5); // Move the bullet upwards
        if (it->getPosition().y < 0) {
            it = bullets.erase(it); // Remove the bullet
        } else {
            ++it;
        }
    }

    // Generate enemies
    if (enemySpawnClock.getElapsedTime().asSeconds() >= enemySpawnInterval) { // Update enemy spawn interval
        enemies.emplace_back(enemyTexture, 2.0f); // Add a new enemy
        enemySpawnClock.restart();
    }

    // Update enemies
    for (auto it = enemies.begin(); it != enemies.end();) {
        it->update();
        if (it->getBounds().top > 1000) { 
            it = enemies.erase(it); 
        } else {
            ++it;
        }
    }

    handlePlayerCollision();

    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
        bool bulletRemoved = false;

        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
            if (bulletIt->getGlobalBounds().intersects(enemyIt->getBounds())) {
                score ++; // Increase the score
                scoreText.setString("Score: " + std::to_string(score)); // Update the score text

                // Collision detected
                enemyIt = enemies.erase(enemyIt); // Remove the enemy
                bulletIt = bullets.erase(bulletIt); // Remove the bullet
                bulletRemoved = true;
                break; // Exit the inner loop
            } else {
                ++enemyIt;
            }
        }

        if (!bulletRemoved) {
            ++bulletIt;
        }
    }

}

void GameScene::handlePlayerCollision() {
    for (auto it = enemies.begin(); it != enemies.end();) {
        // Check for collision with the player
        if (player.getSprite().getGlobalBounds().intersects(it->getBounds())) {
            player.takeDamage(); // Decrease player health
            updateHearts();      // Update the hearts UI

            it = enemies.erase(it);
            if (player.getHealth() == 0) {
                isGameOver = true;
            }
        } else {
            ++it;
        }
    }
}

void GameScene::generateParticle(sf::RenderWindow& window) {

    if (particles.size() > 50) return; 
    // Random number generators with time seed
    static std::mt19937 gen(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));

    std::uniform_real_distribution<float> xDist(0, static_cast<float>(window.getSize().x)); // Random X position
    std::uniform_real_distribution<float> sizeDist(2, 8);  // Random size
    std::uniform_int_distribution<int> colorDist(0, 1);    // Random color (white or gray)

    // Generate random properties for the particle
    float x = xDist(gen);   // Random X position
    float size = sizeDist(gen); // Random size
    float speed = 5.0f;    // Fixed speed
    sf::Color color = colorDist(gen) == 0 ? sf::Color::White : sf::Color(192, 192, 192); // White or gray

    // Add the new particle to the list
    particles.emplace_back(x, 0, size, size, color, speed);
}

void GameScene::setupText(sf::Text& text, const std::string& content, float x, float y) {
    text.setFont(font);
    text.setString(content);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setPosition(x, y);
}

void GameScene::setupHearts(sf::RenderWindow& window) {
    // Get the window width dynamically
    float windowWidth = static_cast<float>(window.getSize().x);

    // Calculate each heart's width after scaling (assuming 10% scale)
    float heartWidth = heartTexture.getSize().x * 0.1f;

    // Position hearts from right to left
    for (int i = 0; i < 3; ++i) {
        hearts[i].setTexture(heartTexture);

        // Scale the hearts to 10% of their original size
        hearts[i].setScale(0.1f, 0.1f);

        // Align hearts to the right, with a spacing of heartWidth + 10px
        hearts[i].setPosition(windowWidth - (heartWidth + 10) * (3 - i), 10);
    }
}


void GameScene::updateHearts() {
    for (int i = 0; i < 3; ++i) {
        if (i < player.getHealth()) {
            hearts[i].setColor(sf::Color::White); // Visible heart
        } else {
            hearts[i].setColor(sf::Color::Transparent); // Invisible heart
        }
    }
}

bool GameScene::isGameOverScreen() const {
    return isGameOver; // Check if the game is over
}

