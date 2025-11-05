#ifndef SCENE06TEXTUREQUAD_H
#define SCENE06TEXTUREQUAD_H

#include <SDL3/SDL_gpu.h>
#include "../Scene.h"
#include <array>
#include <string>

using std::array;
using std::string;

namespace Engine::Scene
{
	class Scene06TextureQuad : public Scene {
	public:
		void Load(Renderer::Renderer& renderer) override;
		bool Update(float dt) override;
		void Draw(Renderer::Renderer& renderer) override;
		void Unload(Renderer::Renderer& renderer) override;
	private:
		array<string, 6> samplerNames{
		"PointClamp",
		"PointWrap",
		"LinearClamp",
		"LinearWrap",
		"AnisotropicClamp",
		"AnisotropicWrap"
		};
		Input::InputState inputState;
		const char* basePath{ nullptr };
		SDL_GPUShader* vertexShader{ nullptr };
		SDL_GPUShader* fragmentShader{ nullptr };
		SDL_GPUGraphicsPipeline* pipeline{ nullptr };
		SDL_GPUBuffer* vertexBuffer{ nullptr };
		SDL_GPUBuffer* indexBuffer{ nullptr };
		SDL_GPUTexture* texture{ nullptr };
		array<SDL_GPUSampler*, 6> samplers{};
		int currentSamplerIndex{ 0 };
	};
}
#endif //SCENE06TEXTUREQUAD_H