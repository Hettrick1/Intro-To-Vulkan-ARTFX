#ifndef SCENE08QUADCLASSTEST_H
#define SCENE08QUADCLASSTEST_H

#include <SDL3/SDL_gpu.h>
#include "../Scene.h"
#include "../../Object/Cube.h"
#include <array>
#include <vector>
#include <string>

namespace Engine::Scene
{
	class Scene08QuadClassTest : public Scene
	{
	public:
		void Load(Renderer::Renderer& renderer) override;
		bool Update(float dt) override;
		void Draw(Renderer::Renderer& renderer) override;
		void Unload(Renderer::Renderer& renderer) override;
	private:
		Input::InputState inputState;
		std::vector<Object::Cube*> quads;
	};
}
#endif