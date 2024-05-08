#pragma once

#include "scenes/scene.hpp"


class NewGame : public AbstractScene {
    public:
        NewGame(MiniEngine::Application* app);
        ~NewGame();

        void init(MiniEngine::Application* app) override;

    private:
        void return_to_main_menu();
        void start_game();

        void start_new_game();
        void load_game();
        void quit_game();

        MiniEngine::Scene* scene;
};
