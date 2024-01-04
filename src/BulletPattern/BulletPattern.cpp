#include "BulletPattern.h"
#include "imgui.h"

BulletPattern::BulletPattern() {
    // @TODO Eventually init a bullet pattern from a file
    patternName = "New Pattern";
}

void BulletPattern::update(float deltaTime, sf::RenderWindow &window) {
    ImGui::Begin("Pattern Editor");

    if (ImGui::Button("Create bullet")) {
        bulletDesignerBullets.emplace_back(
                5,
                bulletDesignerBullets.size() + 1
        );
    }


    for (BulletDesigner &bulletDesignerBullet: bulletDesignerBullets) {
        bulletDesignerBullet.update(deltaTime, window);
    }

    ImGui::End();
}

void BulletPattern::draw(sf::RenderWindow &window) {
    for (BulletDesigner &bulletDesignerBullet: bulletDesignerBullets) {
        bulletDesignerBullet.draw(window);
    }
}