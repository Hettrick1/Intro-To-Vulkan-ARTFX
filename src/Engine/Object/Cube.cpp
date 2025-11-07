#include "Cube.h"

#include "../Renderer/Renderer.h"
#include "../Renderer/PositionTextureVertex.h"

namespace Engine::Object
{
	void Cube::Load(Renderer::Renderer& renderer, SDL_GPUShader* vertShader, SDL_GPUShader* fragShader, const std::string& texturePath)
	{
	}

	void Cube::Draw(Renderer::Renderer& renderer)
	{
		renderer.BindGraphicsPipeline(pipeline);
		SDL_GPUBufferBinding vertexBindings{ .buffer = vertexBuffer, .offset = 0 };
		renderer.BindVertexBuffers(0, vertexBindings, 1);
		SDL_GPUBufferBinding indexBindings{ .buffer = indexBuffer, .offset = 0 };
		renderer.BindIndexBuffer(indexBindings, SDL_GPU_INDEXELEMENTSIZE_16BIT);
		SDL_GPUTextureSamplerBinding textureSamplerBinding{ .texture = texture, .sampler = sampler };
		renderer.BindFragmentSamplers(0, textureSamplerBinding, 1);

		Maths::Mat4 model = Maths::Mat4::CreateRotationMatrix(0.0, 1.0, 0.0, pitch * (SDL_PI_F / 180)) * Maths::Mat4::CreateTranslation(position.x, position.y, position.z);
		Maths::Mat4 view = Maths::Mat4::Identity;
		Maths::Mat4 projection = Maths::Mat4::CreatePerspectiveFieldOfView(90.0f * (SDL_PI_F / 180), 640.0f / 480.0f, 0.1f, 1000.0f);

		Maths::Mat4 mvp = model * view * projection;
		renderer.PushVertexUniformData(0, &mvp, sizeof(mvp));

		FragMultiplyUniform2 fragMultiplyUniform0{ 1.0f, 1.0f, 1.0f, 1.0f };
		renderer.PushFragmentUniformData(0, &fragMultiplyUniform0, sizeof(FragMultiplyUniform2));
		renderer.DrawIndexedPrimitives(36, 1, 0, 0, 0);
	}
	void Cube::Unload(Renderer::Renderer& renderer)
	{
		renderer.ReleaseSampler(sampler);
		renderer.ReleaseBuffer(vertexBuffer);
		renderer.ReleaseBuffer(indexBuffer);
		renderer.ReleaseTexture(texture);
		renderer.ReleaseGraphicsPipeline(pipeline);
	}

	void Cube::SetPosition(const Vector3D& newPosition)
	{
		position = newPosition;
	}

	void Cube::SetPitch(float newPitch)
	{
		pitch = newPitch;
	}
}