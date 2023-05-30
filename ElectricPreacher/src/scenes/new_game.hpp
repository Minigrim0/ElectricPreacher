#pragma once

#include "scenes/scene.hpp"


class NewGame : public Scene {
    public:
        NewGame(MiniEngine::Application* app);
        ~NewGame();

        void init(MiniEngine::Application* app) override;

    private:
        void start_new_game();
        void load_game();
        void quit_game();

        MiniEngine::Scene* scene;
};
