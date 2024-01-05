#include "Menus.h"
#include "imgui.h"

Menus::Menus(Game *_game, Options *_options) : game(_game), options(_options) {
    isOptionsOpen = false;
    windowSize = {1080, 720};
}

void Menus::update() {
    ImGui::Begin("Main Window", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDecoration);

    if (ImGui::BeginMenuBar()) {
        ImGui::SetWindowPos(ImVec2(0, 0));
        ImGui::SetWindowSize({windowSize.x, 0});

        if (ImGui::BeginMenu("Main")) {
            if (ImGui::MenuItem("New Pattern")) {
                game->createBulletPattern();
            }
            if (ImGui::MenuItem("Toggle Settings")) {
                isOptionsOpen = !isOptionsOpen;
            }
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    ImGui::End();

    if (isOptionsOpen) {
        options->update();
    }
}

void Menus::setWindowSize(ImVec2 _windowSize) {
    windowSize = _windowSize;
}