#include "Scene08QuadClassTest.h"

#include "../../Renderer/Renderer.h"
#include "../../Renderer/PositionTextureVertex.h"
#include "../../Maths/Mat4.h"
#include <SDL3/SDL.h>

namespace Engine::Scene
{
	void Scene08QuadClassTest::Load(Renderer::Renderer& renderer)
	{
		quads =
		{
			new Object::Quad(),
			new Object::Quad(),
		};
		auto basePath = SDL_GetBasePath();
		auto vertexShader = renderer.LoadShader(basePath, "TexturedQuadWithMatrix.vert", 0, 1, 0, 0);
		auto fragmentShader = renderer.LoadShader(basePath, "TexturedQuadWithMultiplyColor.frag", 1, 1, 0, 0);

		for (auto quad : quads)
		{
			quad->Load(renderer, "TexturedQuadWithMatrix.vert", "TexturedQuadWithMultiplyColor.frag", "cube0.bmp");
		}
	}

	bool Scene08QuadClassTest::Update(float dt)
	{
		const bool isRunning = ManageInput(inputState);
		return isRunning;
	}

	void Scene08QuadClassTest::Draw(Renderer::Renderer& renderer)
	{
		for (auto quad : quads)
		{
			quad->Draw(renderer);
		}
	}

	void Scene08QuadClassTest::Unload(Renderer::Renderer& renderer)
	{
		for (auto quad : quads)
		{
			quad->Unload(renderer);
			delete quad;
		}
		quads.clear();
	}
}
