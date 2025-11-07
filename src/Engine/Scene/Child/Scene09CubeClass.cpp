#include "Scene09CubeClass.h"

#include "../../Renderer/Renderer.h"
#include "../../Renderer/PositionTextureVertex.h"
#include "../../Maths/Mat4.h"
#include <SDL3/SDL.h>

namespace Engine::Scene
{
	void Scene09CubeClass::Load(Renderer::Renderer& renderer)
	{
		cubes =
		{
			new Object::Cube(),
			new Object::Cube(),
		};
		auto basePath = SDL_GetBasePath();
		auto vertexShader = renderer.LoadShader(basePath, "TexturedQuadWithMatrix.vert", 0, 1, 0, 0);
		auto fragmentShader = renderer.LoadShader(basePath, "TexturedQuadWithMultiplyColor.frag", 1, 1, 0, 0);

		for (auto quad : cubes)
		{
			quad->Load(renderer, vertexShader, fragmentShader, "cube0.bmp");
		}
	}

	bool Scene09CubeClass::Update(float dt)
	{
		const bool isRunning = ManageInput(inputState);
		time += dt * 2;
		for (auto quad : cubes)
		{
			Object::Vector3D position{ quad->GetPosition().x,   SDL_sinf(time),  quad->GetPosition().z };
			quad->SetPosition(position);
			quad->SetPitch(time * 10);
		}
		return isRunning;
	}

	void Scene09CubeClass::Draw(Renderer::Renderer& renderer)
	{
		for (auto quad : cubes)
		{
			quad->Draw(renderer);
		}
	}

	void Scene09CubeClass::Unload(Renderer::Renderer& renderer)
	{
		for (auto quad : cubes)
		{
			quad->Unload(renderer);
			delete quad;
		}
		cubes.clear();
	}
}
