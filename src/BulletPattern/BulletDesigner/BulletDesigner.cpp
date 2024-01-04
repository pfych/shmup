#include <iostream>
#include "BulletDesigner.h"
#include "SFML/Graphics.hpp"
#include "imgui.h"
#include "../../utils/bezierUtils.h"
#include <cmath>

BulletDesigner::BulletDesigner(float _speed, int _identifier) :
        speed(_speed),
        identifier(_identifier) {
    debug = true;
    isClone = false;
    cloneOf = 0;
    name = "New Bullet " + std::to_string(identifier);
    offset = {.x = 0, .y = 0};
    rotation = 0;
}

void BulletDesigner::update(
        float deltaTime,
        sf::RenderWindow &window,
        const std::vector<BulletDesigner> &existingBullets
) {
    std::string headingText = "Bullet " + std::to_string(identifier);

    if (ImGui::CollapsingHeader(headingText.data())) {
        float halfColumnWidth = ImGui::GetContentRegionAvailWidth() * 0.33f;
        float thirdColumnWidth = ImGui::GetContentRegionAvailWidth() * 0.33f;

        ImGui::PushID(std::to_string(identifier).data());

        if (isClone) {
            if (ImGui::BeginCombo("Clone of ", existingBullets[cloneOf].name.data())) {
                for (int i = 0; i < existingBullets.size(); i++) {
                    const bool isSelected = (cloneOf == i);

                    if (!existingBullets[i].isClone || isSelected) {
                        if (ImGui::Selectable(existingBullets[i].name.data(), isSelected)) {
                            cloneOf = i;
                        }
                    }

                    if (isSelected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }

                ImGui::EndCombo();
            }

            ImGui::Text("Offsets");

            ImGui::Columns(2, "Offsets", true);
            ImGui::SetColumnWidth(0, halfColumnWidth);
            ImGui::SetColumnWidth(1, halfColumnWidth);

            ImGui::DragFloat("X##Offset", &offset.x, 1.0f, 200.f, 200.f, "%.3f");
            ImGui::NextColumn();
            ImGui::DragFloat("Y##Offset", &offset.y, 1.0f, 200.f, 200.f, "%.3f");
            ImGui::Columns(1);
            ImGui::DragFloat("rotation", &rotation, 1.f, 1.f, 360.f);

        } else {
            ImGui::InputText("Name", name.data(), 64);

            for (int i = 0; i < points.size(); i++) {
                std::string header = ("Point " + std::to_string(i));
                ImGui::PushID((std::to_string(identifier) + std::to_string(i)).data());
                ImGui::Text(header.data());
                ImGui::Columns(3, (header.data()), true);
                ImGui::SetColumnWidth(0, thirdColumnWidth);
                ImGui::SetColumnWidth(1, thirdColumnWidth);
                ImGui::SetColumnWidth(2, thirdColumnWidth);
                ImGui::DragFloat("X##Start", &points[i].x, 1.0f, 200.f, 200.f, "%.3f");
                ImGui::NextColumn();
                ImGui::DragFloat("Y##Start", &points[i].y, 1.0f, 200.f, 200.f, "%.3f");
                ImGui::NextColumn();
                if (ImGui::Button("Delete")) {
                    points.erase(points.begin() + i);
                }
                ImGui::Columns(1);
                ImGui::PopID();
            }

            if (points.size() < 4) {
                if (ImGui::Button("Add point")) {
                    if (points.empty()) {
                        points.emplace_back(0, 0, true);
                    } else {
                        Point last = points.back();
                        points.emplace_back(last.x + 10, last.y + 10, true);
                    }
                }
            }

            ImGui::Text("Bullet Speed");
            ImGui::DragFloat("speed", &speed, 1.f, 1.f);
            ImGui::Checkbox("Debug", &debug);
        }


        ImGui::Checkbox("Is clone?", &isClone);


        ImGui::PopID();
    }

    if (debug) {
        for (auto &point: points) {
            point.update(deltaTime, window);
        }
    }

    if (isClone) {
        if (!existingBullets[cloneOf].points.empty()) {
            std::vector<Point> newPoints;
            newPoints.reserve(existingBullets.size());

            // Calculate rotations
            double radians = rotation * (M_PI / 180);
            double sinTheta = sin(radians);
            double cosTheta = cos(radians);
            const Point &pivotPoint = existingBullets[cloneOf].points[0];

            for (int i = 0; i < existingBullets[cloneOf].points.size(); i++) {
                const Point originalPoint = existingBullets[cloneOf].points[i];

                Point newPoint = originalPoint;
                newPoint.x += offset.x;
                newPoint.y += offset.y;
                // @TODO This will get stuck if you "un-clone"
                newPoint.color = sf::Color(255, 0, 0, 100);

                if (i != 0) {
                    double translatedX = newPoint.x - pivotPoint.x;
                    double translatedY = newPoint.y - pivotPoint.y;

                    double rotatedX = translatedX * cosTheta - translatedY * sinTheta;
                    double rotatedY = translatedX * sinTheta + translatedY * cosTheta;

                    newPoint.x = rotatedX + pivotPoint.x;
                    newPoint.y = rotatedY + pivotPoint.y;
                }

                newPoints.push_back(newPoint);
            }

            points = newPoints;
            speed = existingBullets[cloneOf].speed;
            debug = existingBullets[cloneOf].debug;
        }
    }
}

void BulletDesigner::draw(sf::RenderWindow &window) const {
    if (debug) {
        for (int i = 0; i < points.size(); i++) {
            Point point = points[i];
            point.draw(window);

            if (i != 0) {
                sf::VertexArray line = createLine(&points[i - 1], &point);
                window.draw(line);
            }
        }
    }
}