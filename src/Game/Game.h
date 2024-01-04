#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "../BulletPattern/BulletPattern.h"

class Game {
public:
    Game();

    void update(float deltaTime, sf::RenderWindow &window, sf::Vector2f mousePositionInView);

    void draw(sf::RenderWindow &window);

    void createBulletPattern();

private:
    std::vector<BulletPattern> bulletPatterns;
    sf::Clock clock;
};
