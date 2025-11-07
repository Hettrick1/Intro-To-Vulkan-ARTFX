#ifndef CUBETEXTURED_H
#define CUBETEXTURED_H

#include "Cube.h"

namespace Engine::Object
{
	class CubeTextured : public Cube
	{
	public:
		CubeTextured() = default;
		~CubeTextured() = default;

		virtual void Load(Renderer::Renderer& renderer, SDL_GPUShader* vertShader, SDL_GPUShader* fragShader, const std::string& texturePath) override;

	private:
	};
}

#endif