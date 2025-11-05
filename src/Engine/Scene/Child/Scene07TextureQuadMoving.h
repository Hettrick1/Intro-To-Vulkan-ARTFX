#ifndef SCENE07TEXTUREQUADMOVING_HPP
#define SCENE07TEXTUREQUADMOVING_HPP

#include <SDL3/SDL_gpu.h>
#include "../Scene.h"
#include <array>
#include <string>

namespace Engine::Scene
{
	typedef struct FragMultiplyUniform
	{
		float r, g, b, a;
	} fragMultiplyUniform;

	class Scene07TextureQuadMoving : public Scene
	{
	public:
		void Load(Renderer::Renderer& renderer) override;
		bool Update(float dt) override;
		void Draw(Renderer::Renderer& renderer) override;
		void Unload(Renderer::Renderer& renderer) override;
	private:
		Input::InputState inputState;
		const char* basePath{ nullptr };
		SDL_GPUShader* vertexShader{ nullptr };
		SDL_GPUShader* fragmentShader{ nullptr };
		SDL_GPUGraphicsPipeline* pipeline{ nullptr };
		SDL_GPUBuffer* vertexBuffer{ nullptr };
		SDL_GPUBuffer* indexBuffer{ nullptr };
		SDL_GPUTexture* texture{ nullptr };
		SDL_GPUSampler* sampler{ nullptr };
		float time{ 0 };
	};
}
#endif