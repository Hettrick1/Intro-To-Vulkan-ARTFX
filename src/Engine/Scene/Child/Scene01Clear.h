#ifndef SCENE01CLEAR_H
#define SCENE01CLEAR_H

#include "../Scene.h"
namespace Engine::Scene
{
	class Scene01Clear : public Scene {
	public:
		void Load(Renderer::Renderer& renderer) override;
		bool Update(float dt) override;
		void Draw(Renderer::Renderer& renderer) override;
		void Unload(Renderer::Renderer& renderer) override;
	private:
		Input::InputState inputState;
	};
}
#endif