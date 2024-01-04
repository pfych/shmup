#include "SFML/Graphics/RenderWindow.hpp"
#include "../BulletPattern/BulletPattern.h"

class Game {
public:
    Game();

    void update(float deltaTime, sf::RenderWindow &window);

    void draw(sf::RenderWindow &window);

private:
    std::vector<BulletPattern> bulletPatterns;
};
