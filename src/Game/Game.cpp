#include "Game.h"
#include "imgui.h"

Game::Game() {
    clock = sf::Clock();
}

void Game::update(float deltaTime, sf::RenderWindow &window) {
    ImGui::Begin("Pattern Creator");

    if (ImGui::Button("Create Pattern")) {
        bulletPatterns.emplace_back(bulletPatterns.size() + 1);
    }

    ImGui::End();

    for (BulletPattern &bulletPattern: bulletPatterns) {
        bulletPattern.update(deltaTime, window, clock);
    }
}

void Game::draw(sf::RenderWindow &window) {
    for (BulletPattern &bulletPattern: bulletPatterns) {
        bulletPattern.draw(window);
    }
}