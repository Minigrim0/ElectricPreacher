#pragma once

#include "scenes/scene.hpp"


class MainMenu : public Scene {
    public:
        MainMenu(MiniEngine::Application* app);
        ~MainMenu();

        void init(MiniEngine::Application* app) override;

    private:
        MiniEngine::Scene* scene;
};
