#ifndef SCENE03VERTEXBUFFER_H
#define SCENE03VERTEXBUFFER_H

#include <SDL3/SDL_gpu.h>
#include "../Scene.h"
namespace Engine::Scene 
{
	class Scene03VertexBuffer : public Scene
	{
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
	};
}
#endif //SCENE03VERTEXBUFFER_H