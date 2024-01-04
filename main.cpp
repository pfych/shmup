#include "SFML/Graphics.hpp"
#include "imgui-SFML.h"
#include "src/Game/Game.h"
#include "src/Menus/Menus.h"

int main() {
    sf::RenderWindow window = sf::RenderWindow(
            {1080, 720},
            "Shmup",
            sf::Style::Titlebar | sf::Style::Close
    );

    sf::View view(sf::FloatRect(0.f, 0.f, 1080.f, 720.f));
    view.setViewport(sf::FloatRect(0, 0, 1, 1));
    window.setView(view);

    ImGui::SFML::Init(window);
    sf::Clock deltaClock;
    Game game;
    Options options(&window, {1920, 1080});
    Menus menu(&game, &options);

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::Resized) {
                window.setView(view);
                menu.setWindowSize({static_cast<float>(event.size.width), static_cast<float>(event.size.height)});
            }
        }

        sf::Vector2 rawMousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f mousePositionInView = window.mapPixelToCoords(rawMousePosition, view);

        window.clear();

        sf::Time delta = deltaClock.restart();
        ImGui::SFML::Update(window, delta);

        game.update(delta.asSeconds(), window, mousePositionInView);
        game.draw(window);
        menu.update();

        ImGui::SFML::Render(window);
        window.display();
    }
}
