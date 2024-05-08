#pragma once

#include <string>
#include <core/application.hpp>

class AbstractScene {
    public:
        AbstractScene(MiniEngine::Application* app, std::string name = "Scene");
        ~AbstractScene();

        virtual void init(MiniEngine::Application* app) = 0;
        void start(MiniEngine::Application* app);

    protected:
        MiniEngine::Scene* m_scene;
};
