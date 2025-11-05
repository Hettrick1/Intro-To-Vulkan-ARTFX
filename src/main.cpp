#include <iostream>
#include <SDL3/SDL_main.h>
#include "Engine/Renderer/Renderer.h"
#include "Engine/Scene/Child/Scene01Clear.h"
#include "Engine/Scene/Child/Scene02Triangle.h"
#include "Engine/Scene/Child/Scene03VertexBuffer.h"
#include "Engine/Scene/Child/Scene04TriangleCullModes.h"
#include "Engine/Scene/Child/Scene05TriangleIndexed.h"
#include "Engine/Time.h"
#include "Engine/Window.h"

using namespace std;
int main(int argc, char** argv) {
	Engine::Window window{};
	Engine::Renderer::Renderer renderer{};
	Engine::Time time{};
	window.Init();
	renderer.Init(window);
	auto scene = std::make_unique<Engine::Scene::Scene05TriangleIndexed>();
	scene->Load(renderer);
	bool isRunning{ true };
	while (isRunning) 
	{
		const float dt = time.ComputeDeltaTime();
		isRunning = scene->Update(dt);
		scene->Draw(renderer);
		time.DelayTime();
	}
	scene->Unload(renderer);
	renderer.Close();
	window.Close();
	return 0;
}