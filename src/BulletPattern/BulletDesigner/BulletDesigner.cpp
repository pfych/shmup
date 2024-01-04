#include <iostream>
#include "BulletDesigner.h"
#include "SFML/Graphics.hpp"
#include "imgui.h"
#include "../../utils/bezierUtils.h"

BulletDesigner::BulletDesigner(float _speed, int _identifier) :
        speed(_speed),
        identifier(_identifier) {
    debug = true;
}

void BulletDesigner::update(float deltaTime, sf::RenderWindow &window) {
    // GUI For managing the path
    std::string headingText = "BulletDesigner " + std::to_string(identifier);
    if (ImGui::CollapsingHeader(headingText.data())) {
        float columnWidth = ImGui::GetContentRegionAvailWidth() * 0.33f; // divide by the number of columns

        ImGui::PushID(std::to_string(identifier).data());

        for (int i = 0; i < points.size(); i++) {
            std::string header = ("Point " + std::to_string(i));
            ImGui::PushID((std::to_string(identifier) + std::to_string(i)).data());
            ImGui::Text(header.data());
            ImGui::Columns(3, (header.data()), true);
            ImGui::SetColumnWidth(0, columnWidth);
            ImGui::SetColumnWidth(1, columnWidth);
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
                    points.emplace_back(0, 0, true, sf::Color(255, 0, 0));
                } else {
                    Point last = points.back();
                    points.emplace_back(last.x + 10, last.y + 10, true, sf::Color(255, 0, 0));
                }
            }
        }

        ImGui::Checkbox("Debug", &debug);
        ImGui::Text("BulletDesigner Speed");
        ImGui::SliderFloat("speed", &speed, 0.f, 100.0f);

        if (debug) {
            std::vector<Point> newMiddles;
            for (auto &point: points) {
                point.update(deltaTime, window);
            }
        }

        ImGui::PopID();
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

        for (int i = 0; i < middles.size(); i++) {
            Point middle = middles[i];
            middle.draw(window);

            if (i != 0) {
                sf::VertexArray line = createLine(&middles[i - 1], &middles[i]);
                window.draw(line);
            }
        }
    }
}