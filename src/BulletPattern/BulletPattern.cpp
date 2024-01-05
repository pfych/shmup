#include <fstream>
#include <iostream>
#include "fmt/format.h"
#include "nlohmann/json.hpp"
#include "BulletPattern.h"
#include "imgui.h"

BulletPattern::BulletPattern(int _identifier, std::vector<BulletPattern> *_existingPatterns) :
        patternName("New Pattern\0", 256),
        identifier(_identifier),
        existingPatterns(_existingPatterns) {
    shotsLeft = 0;
    lastShootTimeMs = 0;
    shotCount = 1;
    isFiring = false;
    delayBetweenShotsMs = 100;
}

void BulletPattern::update(
        float deltaTime,
        sf::RenderWindow &window,
        sf::Vector2f mousePositionInView,
        sf::Clock clock
) {
    std::string headingText = "Pattern Editor " + std::to_string(identifier);
    ImGui::Begin(headingText.data(), nullptr, ImGuiWindowFlags_MenuBar);

    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            std::string saveLabel = fileName.empty() ? "Save" : "Update";
            if (ImGui::MenuItem(saveLabel.data())) {
                save();
            }

            if (ImGui::BeginMenu("Load")) {
                try {
                    for (const auto &entry: std::filesystem::directory_iterator("patterns")) {
                        if (std::filesystem::is_regular_file(entry)) {
                            std::string systemFileName = entry.path().filename().string();

                            if (ImGui::MenuItem(systemFileName.c_str())) {
                                fileName = systemFileName;
                                load();
                            }
                        }
                    }
                } catch (const std::exception &e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }

                ImGui::EndMenu();
            }

            if (ImGui::MenuItem("Exit")) {
                existingPatterns->erase(std::remove_if(existingPatterns->begin(), existingPatterns->end(),
                                                       [this](const BulletPattern &pattern) -> bool {
                                                           return identifier == pattern.identifier;
                                                       }),
                                        existingPatterns->end());
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }


    int timeInMs = clock.getElapsedTime().asMilliseconds();

    ImGui::InputText("Pattern Name", patternName.data(), patternName.size());
    ImGui::DragInt("Delay between shotCount", &delayBetweenShotsMs, 1.f);
    ImGui::DragInt("Number of shotCount", &shotCount, 1.f);

    float columnWidth = ImGui::GetContentRegionAvail().x * 0.33f;
    ImGui::Columns(3, "MainButtons", true);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::SetColumnWidth(1, columnWidth);
    ImGui::SetColumnWidth(2, columnWidth);

    if (ImGui::Button("Fire")) {
        isFiring = true;
        shotsLeft = shotCount;
    }

    ImGui::NextColumn();

    if (ImGui::Button("Clean")) {
        bullets = {};
    }

    ImGui::NextColumn();

    if (ImGui::Button("Create bullet")) {
        bulletDesignerBullets.emplace_back(
                5,
                bulletDesignerBullets.size() + 1,
                "New Bullet " + std::to_string(bulletDesignerBullets.size() + 1),
                std::vector<Point>{},
                false,
                0,
                Coordinate{0, 0},
                0.f
        );
    }

    ImGui::Columns(1);

    for (BulletDesigner &bulletDesignerBullet: bulletDesignerBullets) {
        bulletDesignerBullet.update(deltaTime, mousePositionInView, bulletDesignerBullets);
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
            if (timeInMs > lastShootTimeMs + delayBetweenShotsMs) {
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

void BulletPattern::save() {
    nlohmann::json saveData;

    saveData["patternName"] = patternName.data();
    saveData["shotCount"] = shotCount;
    saveData["delayBetweenShotsMs"] = delayBetweenShotsMs;
    saveData["bullets"] = [this]() -> nlohmann::json {
        nlohmann::json bulletData;

        for (BulletDesigner bulletDesignerBullet: bulletDesignerBullets) {
            bulletData.push_back({
                                         {"name",     bulletDesignerBullet.name.data()},
                                         {"speed",    bulletDesignerBullet.speed},
                                         {"isClone",  bulletDesignerBullet.isClone},
                                         {"cloneOf",  bulletDesignerBullet.cloneOf},
                                         {"offset",   {
                                                              {"x", bulletDesignerBullet.offset.x},
                                                              {"y", bulletDesignerBullet.offset.y}
                                                      }},
                                         {"rotation", bulletDesignerBullet.rotation},
                                         {"points",   [bulletDesignerBullet]() -> nlohmann::json {
                                             nlohmann::json pointData;

                                             for (Point point: bulletDesignerBullet.points) {
                                                 pointData.push_back({
                                                                             {"x", point.x},
                                                                             {"y", point.y}
                                                                     });
                                             }

                                             return pointData;
                                         }()}
                                 });
        }

        return bulletData;
    }();

    std::string saveFileName;
    if (fileName.empty()) {
        saveFileName = fmt::format("{}.json", patternName.data());
    } else {
        saveFileName = fileName;
    }
    fileName = saveFileName;

    std::string parentFolder = "patterns";
    std::string filePath = fmt::format("{}/{}", parentFolder, saveFileName);

    if (!std::filesystem::exists(parentFolder)) {
        std::filesystem::create_directory(parentFolder);
    }

    std::ofstream outputFile(filePath);
    if (outputFile.is_open()) {
        outputFile << std::setw(4) << saveData << std::endl;
        outputFile.close();
        std::cout << fmt::format("JSON data saved to {}\n", filePath);
    } else {
        std::cerr << fmt::format("Error opening {} for writing\n", filePath);
    }
}

void BulletPattern::load() {
    if (fileName.empty()) {
        std::cerr << "No filename set!\n";
        return;
    }

    std::string parentFolder = "patterns";
    std::string filePath = fmt::format("{}/{}", parentFolder, fileName);

    std::ifstream outputFile(filePath);
    if (outputFile.is_open()) {
        nlohmann::json jsonData;
        outputFile >> jsonData;

        patternName = jsonData["patternName"];
        shotCount = jsonData["shotCount"];
        delayBetweenShotsMs = jsonData["delayBetweenShotsMs"];

        bulletDesignerBullets = {};
        for (nlohmann::json bulletData: jsonData["bullets"]) {
            bulletDesignerBullets.emplace_back(
                    bulletData["speed"],
                    bulletDesignerBullets.size() + 1,
                    bulletData["name"],
                    [bulletData]() -> std::vector<Point> {
                        std::vector<Point> bulletDesignerBulletPoints;

                        for (nlohmann::json pointData: bulletData["points"]) {
                            bulletDesignerBulletPoints.emplace_back(pointData["x"], pointData["y"], true);
                        }

                        return bulletDesignerBulletPoints;
                    }(),
                    bulletData["isClone"],
                    bulletData["cloneOf"],
                    Coordinate{bulletData["offset"]["x"], bulletData["offset"]["y"]},
                    bulletData["rotation"]
            );
        }

        outputFile.close();
        std::cout << fmt::format("JSON data Read from {}\n", filePath);
    } else {
        std::cerr << fmt::format("Error opening {} for reading\n", filePath);
    }
}