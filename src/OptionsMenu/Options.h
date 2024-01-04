#include "SFML/Graphics.hpp"

class Options {
public:
    Options(sf::VideoMode _resolution);

    void update(sf::RenderWindow &window);

    void draw(sf::RenderWindow &window);

private:
    bool fullscreen;
    sf::VideoMode resolution;
    int selectedResolutionIndex;

    static std::string getPrettyResolutionName(sf::VideoMode _resolution);

    std::vector<sf::VideoMode> validResolutions = {{720,  480},
                                                   {1080, 720},
                                                   {1920, 1080}};
};

