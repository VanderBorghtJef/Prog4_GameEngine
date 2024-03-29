#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextRenderComponent.h"
#include "TextureRenderComponent.h"
#include "FPSComponent.h"
#include "CircleRotationComponent.h"
#include "BasicMovement.h"
#include "Controller.h"
#include "Keyboard.h"

void load()
{

	InputDevice* controller0 = dae::InputManager::GetInstance().AddInputDevice<Controller>(0);
	InputDevice* keyboard = dae::InputManager::GetInstance().AddInputDevice<Keyboard>();

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	// Background
	auto background = new dae::GameObject();
	background->AddComponent<TextureRenderComponent>("background.tga");
	scene.Add(background);

	// Logo
	auto logo = new dae::GameObject();
	logo->AddComponent<TextureRenderComponent>("logo.tga");
	logo->SetLocalPosition(216, 180);
	scene.Add(logo);

	// Text
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textTitle = new dae::GameObject();
	textTitle->AddComponent<TextRenderComponent>("Programming 4 Assignment", font);
	textTitle->SetLocalPosition(80, 20);
	scene.Add(textTitle);

	// FPS counter
	auto FPSCounter = new dae::GameObject();
	FPSCounter->AddComponent<TextRenderComponent>("test", font);
	FPSCounter->AddComponent<FPSComponent>();
	FPSCounter->SetLocalPosition(0, 0);
	scene.Add(FPSCounter);


	float movementSpeed{ 100.0f };

	// Character 1
	auto character1 = new dae::GameObject();
	character1->SetLocalPosition(0,0);
	character1->AddComponent<TextureRenderComponent>("../Data/PacMan.png");
	character1->AddComponent<BasicMovement>(movementSpeed, keyboard);
	scene.Add(character1);

	// Character 2
	auto character2 = new dae::GameObject();
	character2->SetLocalPosition(0, 0);
	character2->AddComponent<TextureRenderComponent>("../Data/PacWoman.png");
	character2->AddComponent<BasicMovement>(movementSpeed * 2, controller0);
	scene.Add(character2);
	
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}