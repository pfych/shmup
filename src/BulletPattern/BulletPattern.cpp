#include "BulletPattern.h"
#include "imgui.h"

BulletPattern::BulletPattern() {
    // @TODO Eventually init a bullet pattern from a file
    patternName = "New Pattern";
}

void BulletPattern::update(float deltaTime, sf::RenderWindow &window) {
    ImGui::Begin("Pattern Editor");

    if (ImGui::Button("Create bullet")) {
        bullets.emplace_back(
                5,
                bullets.size() + 1
        );
    }


    for (Bullet &bullet: bullets) {
        bullet.update(deltaTime, window);
    }

    ImGui::End();
}

void BulletPattern::draw(sf::RenderWindow &window) {
    for (Bullet &bullet: bullets) {
        bullet.draw(window);
    }
}