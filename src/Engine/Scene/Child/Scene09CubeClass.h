#ifndef SCENE09CUBECLASS_H
#define SCENE09CUBECLASS_H

#include <SDL3/SDL_gpu.h>
#include "../Scene.h"
#include "../../Object/Cube.h"
#include <array>
#include <vector>
#include <string>

namespace Engine::Scene
{
	class Scene09CubeClass : public Scene
	{
	public:
		void Load(Renderer::Renderer& renderer) override;
		bool Update(float dt) override;
		void Draw(Renderer::Renderer& renderer) override;
		void Unload(Renderer::Renderer& renderer) override;
	private:
		Input::InputState inputState;
		std::vector<Object::Cube*> cubes;
		float time{ 0 };
	};
}
#endif