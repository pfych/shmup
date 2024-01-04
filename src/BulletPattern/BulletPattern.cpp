#include "BulletPattern.h"
#include "imgui.h"

BulletPattern::BulletPattern(int _identifier) {
    patternName = "New Pattern";
    identifier = _identifier;
    shotsLeft = 0;
    lastShootTimeMs = 0;
    shots = 1;
    isFiring = false;
    betweenDelayMs = 100;
}

void BulletPattern::update(float deltaTime, sf::RenderWindow &window, sf::Clock clock) {
    std::string headingText = "Pattern Editor " + std::to_string(identifier);
    ImGui::Begin(headingText.data());

    int timeInMs = clock.getElapsedTime().asMilliseconds();

    ImGui::InputText("Pattern Name", patternName.data(), patternName.size());
    ImGui::DragInt("Delay between shots", &betweenDelayMs, 1.f);
    ImGui::DragInt("Number of shots", &shots, 1.f);

    float columnWidth = ImGui::GetContentRegionAvailWidth() * 0.33f;
    ImGui::Columns(3, "MainButtons", true);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::SetColumnWidth(1, columnWidth);
    ImGui::SetColumnWidth(2, columnWidth);

    if (ImGui::Button("Fire")) {
        isFiring = true;
        shotsLeft = shots;
    }

    ImGui::NextColumn();

    if (ImGui::Button("Clean")) {
        bullets = {};
    }

    ImGui::NextColumn();

    if (ImGui::Button("Create bullet")) {
        bulletDesignerBullets.emplace_back(
                5,
                bulletDesignerBullets.size() + 1
        );
    }

    ImGui::Columns(1);

    for (BulletDesigner &bulletDesignerBullet: bulletDesignerBullets) {
        bulletDesignerBullet.update(deltaTime, window, bulletDesignerBullets);
    }

    for (Bullet &bullet: bullets) {
        bullet.update(deltaTime);

    }

    std::vector<int> bulletsToRemove;
    for (int i = 0; i < bullets.size(); i++) {
        Bullet bullet = bullets[i];

        if (bullet.isOffScreen(window)) {
            bulletsToRemove.push_back(i);
        }
    }

    for (int bulletToRemove: bulletsToRemove) {
        bullets.erase(bullets.begin() + bulletToRemove);
    }

    if (isFiring) {
        if (shotsLeft > 0) {
            if (timeInMs > lastShootTimeMs + betweenDelayMs) {
                lastShootTimeMs = timeInMs;
                shotsLeft -= 1;
                for (const BulletDesigner &bulletDesignerBullet: bulletDesignerBullets) {
                    bullets.emplace_back(bulletDesignerBullet.speed, bulletDesignerBullet.points);
                }
            }
        }
    }

    ImGui::End();
}

void BulletPattern::draw(sf::RenderWindow &window) {
    for (BulletDesigner &bulletDesignerBullet: bulletDesignerBullets) {
        bulletDesignerBullet.draw(window);
    }

    for (Bullet &bullet: bullets) {
        bullet.draw(window);
    }
}