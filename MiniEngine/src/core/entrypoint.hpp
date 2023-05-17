#pragma once

#ifdef ME_PLATFORM_WINDOWS

extern MiniEngine::Application* MiniEngine::CreateApplication();

int main(int argc, char** argv) {
	MiniEngine::Log::init();

	ME_CORE_INFO("Creating the application");
	auto app = MiniEngine::CreateApplication();
	ME_CORE_INFO("Application created!");
	
	app->Run();
	delete app;

	return 0;
}

#endif