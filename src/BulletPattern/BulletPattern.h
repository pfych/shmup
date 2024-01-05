#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "BulletDesigner/BulletDesigner.h"
#include "Bullet/Bullet.h"
#include "../Game/Game.h"


class BulletPattern {
public:
    BulletPattern(int _identifier, std::vector<BulletPattern> *_existingPatterns);

    void update(float deltaTime, sf::RenderWindow &window, sf::Vector2f mousePositionInView, sf::Clock clock);

    void draw(sf::RenderWindow &window);

    void save();

    void load();


private:
    std::vector<BulletPattern> *existingPatterns;
    std::string fileName;
    std::string patternName;
    int shotCount;
    int delayBetweenShotsMs;
    std::vector<BulletDesigner> bulletDesignerBullets;

    int identifier;
    bool isFiring;
    int shotsLeft;
    int lastShootTimeMs;
    std::vector<Bullet> bullets;
};