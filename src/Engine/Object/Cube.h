#ifndef CUBE_H
#define CUBE_H

#include "../Maths/Mat4.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>
#include <array>
#include <string>

namespace Engine::Renderer
{
	class Renderer;
}

namespace Engine::Object
{
	typedef struct FragMultiplyUniform2
	{
		float r, g, b, a;
	} FragMultiplyUniform2;

	typedef struct Vector3D
	{
		float x, y, z;
	} Vector3D;

	class Cube
	{
	public:
		Cube() = default;
		~Cube() = default;

		void Load(Renderer::Renderer& renderer, SDL_GPUShader* vertShader, SDL_GPUShader* fragShader, const std::string& texturePath);
		void Draw(Renderer::Renderer& renderer);
		void Unload(Renderer::Renderer& renderer);

		void SetPosition(const Vector3D& position);
		void SetPitch(float newPitch);

		inline Vector3D GetPosition() const { return position; }

	private:
		const char* basePath{ nullptr };
		SDL_GPUShader* vertexShader{ nullptr };
		SDL_GPUShader* fragmentShader{ nullptr };
		SDL_GPUGraphicsPipeline* pipeline{ nullptr };
		SDL_GPUBuffer* vertexBuffer{ nullptr };
		SDL_GPUBuffer* indexBuffer{ nullptr };
		SDL_GPUTexture* texture{ nullptr };
		SDL_GPUSampler* sampler{ nullptr };
		Vector3D position{ 0, 0, -2 };
		float pitch{ 0 };
	};
}

#endif