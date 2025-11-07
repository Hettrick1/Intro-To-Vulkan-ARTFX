#ifndef CUBETINDEXED_H
#define CUBETINDEXED_H

#include "Cube.h"

namespace Engine::Object
{
	class CubeIndexed : public Cube
	{
	public:
		CubeIndexed() = default;
		~CubeIndexed() = default;

		virtual void Load(Renderer::Renderer& renderer, SDL_GPUShader* vertShader, SDL_GPUShader* fragShader, const std::string& texturePath) override;

	private:
	};
}

#endif