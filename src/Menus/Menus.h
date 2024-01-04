#pragma once

#include "imgui.h"
#include "../Game/Game.h"
#include "../OptionsMenu/Options.h"

class Menus {
public:
    explicit Menus(Game *_game, Options *_options);

    void update();

    void setWindowSize(ImVec2 _windowSize);

private:
    ImVec2 windowSize;
    bool isOptionsOpen;
    Game *game;
    Options *options{};
};
