#pragma once

#ifdef ME_PLATFORM_WINDOWS

extern MiniEngine::Application* MiniEngine::CreateApplication();

int main(int argc, char** argv) {
	MiniEngine::Log::init();
	ME_CORE_WARN("Initialized Log!");
	int a = 5;
	ME_INFO("Hello! Var={0}", a);

	auto app = MiniEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif