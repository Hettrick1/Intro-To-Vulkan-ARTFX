#ifndef CUBE_H
#define CUBE_H

#include <SDL3/SDL_gpu.h>
#include <array>
#include <string>

namespace Engine::Renderer
{
	class Renderer;
}

namespace Engine::Object
{
	typedef struct FragMultiplyUniform
	{
		float r, g, b, a;
	} fragMultiplyUniform;

	class Cube
	{
	public:
		Cube() = default;
		~Cube() = default;

		void Load(Renderer::Renderer& renderer, SDL_GPUShader* vertShader, SDL_GPUShader* fragShader, const std::string& texturePath);
		void Draw(Renderer::Renderer& renderer);
		void Unload(Renderer::Renderer& renderer);

	private:
		const char* basePath{ nullptr };
		SDL_GPUShader* vertexShader{ nullptr };
		SDL_GPUShader* fragmentShader{ nullptr };
		SDL_GPUGraphicsPipeline* pipeline{ nullptr };
		SDL_GPUBuffer* vertexBuffer{ nullptr };
		SDL_GPUBuffer* indexBuffer{ nullptr };
		SDL_GPUTexture* texture{ nullptr };
		SDL_GPUSampler* sampler{ nullptr };
	};
}

#endif