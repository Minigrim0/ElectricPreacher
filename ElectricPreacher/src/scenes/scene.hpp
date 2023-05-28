#pragma once

#include <string>
#include <core/application.hpp>

class Scene{
    public:
        Scene(MiniEngine::Application* app, std::string name = "Scene");
        ~Scene();

        virtual void init(MiniEngine::Application* app) = 0;
        void start(MiniEngine::Application* app);

    protected:
        MiniEngine::Scene* m_scene;
};
