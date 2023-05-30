#pragma once

#include "scenes/scene.hpp"


class MainMenu : public Scene {
    public:
        MainMenu(MiniEngine::Application* app);
        ~MainMenu();

        void init(MiniEngine::Application* app) override;

    private:
        void start_new_game();
        void load_game();
        void quit_game();

        MiniEngine::Scene* scene;
};
