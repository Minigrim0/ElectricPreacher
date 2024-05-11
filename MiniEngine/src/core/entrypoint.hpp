#pragma once

extern MiniEngine::Application *MiniEngine::CreateApplication();

int main(int argc, char *argv[]) {
    MiniEngine::Log::init();

    ME_CORE_INFO("Creating the application");
    auto app = MiniEngine::CreateApplication();
    app->run();
    delete app;

    return 0;
}
