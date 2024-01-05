#include "Game.h"
#include "imgui.h"

Game::Game() {
    clock = sf::Clock();
}

void Game::update(float deltaTime, sf::RenderWindow &window, sf::Vector2f mousePositionInView) {
    for (BulletPattern &bulletPattern: bulletPatterns) {
        bulletPattern.update(deltaTime, window, mousePositionInView, clock);
    }
}

void Game::draw(sf::RenderWindow &window) {
    for (BulletPattern &bulletPattern: bulletPatterns) {
        bulletPattern.draw(window);
    }
}

void Game::createBulletPattern() {
    bulletPatterns.emplace_back(bulletPatterns.size() + 1, &bulletPatterns);
}