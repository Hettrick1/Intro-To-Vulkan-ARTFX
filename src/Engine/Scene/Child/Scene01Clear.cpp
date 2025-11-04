#include "Scene01Clear.h"
#include "../../Renderer/Renderer.h"
#include <SDL3/SDL_events.h>

namespace Engine::Scene
{
	void Scene01Clear::Load(Renderer::Renderer& renderer) {
	}
	bool Scene01Clear::Update(float dt) {
		return ManageInput(inputState);
	}
	void Scene01Clear::Draw(Renderer::Renderer& renderer) {
		renderer.Begin();
		renderer.End();
	}
	void Scene01Clear::Unload(Renderer::Renderer& renderer) {
	}
}