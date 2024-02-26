#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextRenderComponent.h"
#include "TextureRenderComponent.h"
#include "FPSComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	// Background
	auto background = std::make_shared<dae::GameObject>();
	background->AddComponent<TextureRenderComponent>("background.tga");
	scene.Add(background);

	// Logo
	auto logo = std::make_shared<dae::GameObject>();
	logo->AddComponent<TextureRenderComponent>("logo.tga");
	logo->SetLocalPosition(216, 180);
	scene.Add(logo);

	// Text
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textTitle = std::make_shared<dae::GameObject>();
	textTitle->AddComponent<TextRenderComponent>("Programming 4 Assignment", font);
	textTitle->SetLocalPosition(80, 20);
	scene.Add(textTitle);

	// FPS counter
	auto FPSCounter = std::make_shared<dae::GameObject>();
	FPSCounter->AddComponent<TextRenderComponent>("test", font);
	FPSCounter->AddComponent<FPSComponent>();
	FPSCounter->SetLocalPosition(0, 0);
	scene.Add(FPSCounter);
	
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}