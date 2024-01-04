#pragma once

#include "SFML/Graphics.hpp"

class Options {
public:
    explicit Options(sf::RenderWindow *_window, sf::VideoMode _resolution);

    void update();

private:
    bool fullscreen;
    sf::VideoMode resolution;
    sf::RenderWindow *window;
    int selectedResolutionIndex;

    static std::string getPrettyResolutionName(sf::VideoMode _resolution);

    std::vector<sf::VideoMode> validResolutions = {{720,  480},
                                                   {1080, 720},
                                                   {1920, 1080}};
};

