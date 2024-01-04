#include "Options.h"
#include "imgui.h"


Options::Options(sf::VideoMode _resolution) {
    resolution = _resolution;
    fullscreen = false;
    selectedResolutionIndex = 0;
}

std::string Options::getPrettyResolutionName(sf::VideoMode _resolution) {
    return std::to_string(_resolution.width)
           + "x"
           + std::to_string(_resolution.height);
}

void Options::update(sf::RenderWindow &window) {
    ImGui::Begin("Options");

    if (ImGui::BeginCombo("Resolution ", getPrettyResolutionName(validResolutions[selectedResolutionIndex]).c_str())) {
        for (int i = 0; i < validResolutions.size(); i++) {
            const bool isSelected = (selectedResolutionIndex == i);

            if (ImGui::Selectable(getPrettyResolutionName(validResolutions[i]).c_str(), isSelected)) {
                selectedResolutionIndex = i;
            }

            if (isSelected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    ImGui::Checkbox("Fullscreen", &fullscreen);

    if (ImGui::Button("Apply")) {
        if (fullscreen) {
            window.create(
                    sf::VideoMode(validResolutions[selectedResolutionIndex]),
                    "Shmup",
                    sf::Style::Fullscreen
            );
        } else {
            window.create(
                    sf::VideoMode(validResolutions[selectedResolutionIndex]),
                    "Shmup",
                    sf::Style::Titlebar | sf::Style::Close
            );
        }
    }
    ImGui::End();
}