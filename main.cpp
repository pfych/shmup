#include <iostream>
#include "SFML/Graphics.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include "src/Game/Game.h"

int main() {
    auto window = sf::RenderWindow({1080, 720}, "Shmup");
    ImGui::SFML::Init(window);

    sf::Clock deltaClock;
    sf::Clock clock;
    Game game;

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        sf::Time delta = deltaClock.restart();
        ImGui::SFML::Update(window, delta);

        game.update(delta.asSeconds(), window);
        game.draw(window);

        ImGui::SFML::Render(window);
        window.display();
    }
}
