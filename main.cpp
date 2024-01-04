#include "SFML/Graphics.hpp"
#include "imgui-SFML.h"
#include "src/Game/Game.h"
#include "src/OptionsMenu/Options.h"

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
    sf::Clock clock;
    Game game;
    Options options({720, 1080});

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::Resized) {
                window.setView(view);
            }
        }

        window.clear();

        sf::Time delta = deltaClock.restart();
        ImGui::SFML::Update(window, delta);

        options.update(window);

        game.update(delta.asSeconds(), window, view);
        game.draw(window);

        ImGui::SFML::Render(window);
        window.display();
    }
}
