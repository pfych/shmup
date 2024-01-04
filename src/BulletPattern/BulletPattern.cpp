#include "BulletPattern.h"
#include "imgui.h"

BulletPattern::BulletPattern() {
    // @TODO Eventually init a bullet pattern from a file
    patternName = "New Pattern";
    shotsLeft = 0;
    lastShootTimeMs = 0;
    shots = 1;
    isFiring = false;
    betweenDelayMs = 100;
}

void BulletPattern::update(float deltaTime, sf::RenderWindow &window, sf::Clock clock) {
    ImGui::Begin("Pattern Editor");
    int timeInMs = clock.getElapsedTime().asMilliseconds();

    ImGui::DragInt("Delay between shots", &betweenDelayMs, 1.f);
    ImGui::DragInt("Number of shots", &shots, 1.f);

    if (ImGui::Button("Fire")) {
        isFiring = true;
        shotsLeft = shots;
    }

    if (ImGui::Button("Create bullet")) {
        bulletDesignerBullets.emplace_back(
                5,
                bulletDesignerBullets.size() + 1
        );
    }


    for (BulletDesigner &bulletDesignerBullet: bulletDesignerBullets) {
        bulletDesignerBullet.update(deltaTime, window);
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