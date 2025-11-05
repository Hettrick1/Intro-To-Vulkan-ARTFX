#ifndef SCENE05TRIANGLEINDEXED_H
#define SCENE05TRIANGLEINDEXED_H

#include <SDL3/SDL_gpu.h>
#include "../Scene.h"
#include <array>
#include <string>

using std::array;
using std::string;
namespace Engine::Scene
{
	class Scene05TriangleIndexed : public Scene {
	public:
		void Load(Renderer::Renderer& renderer) override;
		bool Update(float dt) override;
		void Draw(Renderer::Renderer& renderer) override;
		void Unload(Renderer::Renderer& renderer) override;
	private:
		Input::InputState inputState;
		const char* basePath;
		SDL_GPUShader* vertexShader;
		SDL_GPUShader* fragmentShader;
		SDL_GPUGraphicsPipeline* pipeline;
		SDL_GPUBuffer* vertexBuffer;
		SDL_GPUBuffer* indexBuffer;
		bool useIndexBuffer{ true };
	};
}
#endif //SCENE05TRIANGLEINDEXED_H