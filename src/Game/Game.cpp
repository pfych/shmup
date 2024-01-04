#include "Game.h"
#include "imgui.h"

Game::Game() {

}

void Game::update(float deltaTime, sf::RenderWindow &window) {
    ImGui::Begin("Pattern Creator");

    if (ImGui::Button("Create Pattern")) {
        bulletPatterns.emplace_back();
    }

    ImGui::End();

    for (BulletPattern &bulletPattern: bulletPatterns) {
        bulletPattern.update(deltaTime, window);
    }
}

void Game::draw(sf::RenderWindow &window) {
    for (BulletPattern &bulletPattern: bulletPatterns) {
        bulletPattern.draw(window);
    }
}