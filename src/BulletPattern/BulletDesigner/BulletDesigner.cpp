#include <iostream>
#include "BulletDesigner.h"
#include "SFML/Graphics.hpp"
#include "imgui.h"
#include "../../utils/bezierUtils.h"

BulletDesigner::BulletDesigner(float _speed, int _identifier) :
        speed(_speed),
        identifier(_identifier) {
    distance = 50;
    debug = true;
}

Point amplify(Point point, float amplification) {
    point.x *= amplification;
    point.y *= amplification;

    return point;
}

void BulletDesigner::update(float deltaTime, sf::RenderWindow &window) {
    // GUI For managing the path
    std::string headingText = "BulletDesigner " + std::to_string(identifier);
    if (ImGui::CollapsingHeader(headingText.data())) {
        float columnWidth = ImGui::GetContentRegionAvailWidth() * 0.33f; // divide by the number of columns

        for (int i = 0; i < points.size(); i++) {
            std::string header = ("Point " + std::to_string(i));
            ImGui::PushID(i);
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
        ImGui::Text("Distance along line");
        ImGui::SliderFloat("Distance", &distance, 0.f, 100.0f);
    }

    if (distance >= 100) {
        distance = 0;
    } else {
        distance += speed * deltaTime;
    }

    float distanceAsRange = distance / 100;

    if (points.size() == 2) {
        position = lerp(points[0], points[1], distanceAsRange);
    } else if (points.size() == 3) {
        position = BezierPoint(points[0], points[1], points[2], distanceAsRange);
    } else if (points.size() == 4) {
        position = BezierPoint(points[0], points[1], points[2], points[3], distanceAsRange);
    }

    if (debug) {
        std::vector<Point> newMiddles;
        for (int i = 0; i < points.size(); i++) {
            points[i].update(deltaTime, window);

            if (points.size() >= 2) {
                if (i != 0) {
                    Coordinate middle = lerp(points[i - 1], points[i], distanceAsRange);
                    newMiddles.emplace_back(middle.x, middle.y, false, sf::Color(0, 255, 0));
                }
            }
        }
        middles = newMiddles;
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

    sf::CircleShape bulletShape(5.f);
    bulletShape.setFillColor(sf::Color(0, 0, 255));
    bulletShape.setPosition(position.x, position.y);
    window.draw(bulletShape);
}