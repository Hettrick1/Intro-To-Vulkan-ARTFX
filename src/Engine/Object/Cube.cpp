#include "Cube.h"

#include "../Renderer/Renderer.h"
#include "../Renderer/PositionTextureVertex.h"
#include "../Maths/Mat4.h"
#include <SDL3/SDL.h>

namespace Engine::Object
{
	void Cube::Load(Renderer::Renderer& renderer, SDL_GPUShader* vertShader, SDL_GPUShader* fragShader, const std::string& texturePath)
	{
		basePath = SDL_GetBasePath();
		vertexShader = vertShader;
		fragmentShader = fragShader;
		SDL_Surface* imageData = renderer.LoadBMPImage(basePath, texturePath.c_str(), 4);
		if (imageData == nullptr)
		{
			SDL_Log("Could not load image data!");
		}

		// Create the pipeline
		SDL_GPUGraphicsPipelineCreateInfo pipelineCreateInfo = {
		.vertex_shader = vertexShader,
		.fragment_shader = fragmentShader,
		// This is set up to match the vertex shader layout!
		.vertex_input_state = SDL_GPUVertexInputState {
		.vertex_buffer_descriptions = new SDL_GPUVertexBufferDescription[1] {{
		.slot = 0,
		.pitch = sizeof(PositionTextureVertex),
		.input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX,
		.instance_step_rate = 0,
		}},
		.num_vertex_buffers = 1,
		.vertex_attributes = new SDL_GPUVertexAttribute[2] {{
		.location = 0,
		.buffer_slot = 0,
		.format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
		.offset = 0
		}, {
		.location = 1,
		.buffer_slot = 0,
		.format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2,
		.offset = sizeof(float) * 3
		}},
		.num_vertex_attributes = 2,
		},

		.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
		.target_info = {
		.color_target_descriptions = new SDL_GPUColorTargetDescription[1] {{
		.format = SDL_GetGPUSwapchainTextureFormat(renderer.device,
		renderer.renderWindow),
		.blend_state = {
		.src_color_blendfactor = SDL_GPU_BLENDFACTOR_SRC_ALPHA,
		.dst_color_blendfactor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
		.color_blend_op = SDL_GPU_BLENDOP_ADD,
		.src_alpha_blendfactor = SDL_GPU_BLENDFACTOR_SRC_ALPHA,
		.dst_alpha_blendfactor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
		.alpha_blend_op = SDL_GPU_BLENDOP_ADD,
		.enable_blend = true,
		}
		}},
		.num_color_targets = 1,
		},
		};
		pipeline = renderer.CreateGPUGraphicsPipeline(pipelineCreateInfo);

		// Clean up shader resources
		renderer.ReleaseShader(vertexShader);
		renderer.ReleaseShader(fragmentShader);

		// Texture sampler
		sampler = renderer.CreateSampler(SDL_GPUSamplerCreateInfo{
		.min_filter = SDL_GPU_FILTER_NEAREST,
		.mag_filter = SDL_GPU_FILTER_NEAREST,
		.mipmap_mode = SDL_GPU_SAMPLERMIPMAPMODE_NEAREST,
		.address_mode_u = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
		.address_mode_v = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
		.address_mode_w = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE,
			});

		// Create the vertex buffer
		SDL_GPUBufferCreateInfo vertexBufferCreateInfo = {
		.usage = SDL_GPU_BUFFERUSAGE_VERTEX,
		.size = sizeof(PositionTextureVertex) * 8
		};
		vertexBuffer = renderer.CreateBuffer(vertexBufferCreateInfo);
		renderer.SetBufferName(vertexBuffer, "Ravioli Vertex Buffer");

		// Create the index buffer
		SDL_GPUBufferCreateInfo indexBufferCreateInfo = {
		.usage = SDL_GPU_BUFFERUSAGE_INDEX,
		.size = sizeof(Uint16) * 36
		};
		indexBuffer = renderer.CreateBuffer(indexBufferCreateInfo);

		// Create texture
		SDL_GPUTextureCreateInfo textureInfo{
		.type = SDL_GPU_TEXTURETYPE_2D,
		.format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM,
		.usage = SDL_GPU_TEXTUREUSAGE_SAMPLER,
		.width = static_cast<Uint32>(imageData->w),
		.height = static_cast<Uint32>(imageData->h),
		.layer_count_or_depth = 1,
		.num_levels = 1,
		};

		texture = renderer.CreateTexture(textureInfo);
		renderer.SetTextureName(texture, "Ravioli Texture");

		// Set the buffer data
		SDL_GPUTransferBufferCreateInfo transferBufferCreateInfo = {
		.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
		.size = (sizeof(PositionTextureVertex) * 8) + (sizeof(Uint16) * 36),
		};
		SDL_GPUTransferBuffer* transferBuffer = renderer.CreateTransferBuffer(transferBufferCreateInfo);

		// Map the transfer buffer and fill it with data (data is bound to the transfer buffer)
		auto transferData = static_cast<PositionTextureVertex*>(renderer.MapTransferBuffer(transferBuffer, false));

		transferData[0] = { -0.5f, -0.5f, -0.5f, 0.0f, 1.0f };
		transferData[1] = { 0.5f, -0.5f, -0.5f, 1.0f, 1.0f }; 
		transferData[2] = { 0.5f,  0.5f, -0.5f, 1.0f, 0.0f }; 
		transferData[3] = { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f };
		transferData[4] = { -0.5f, -0.5f,  0.5f, 0.0f, 1.0f };
		transferData[5] = { 0.5f, -0.5f,  0.5f, 1.0f, 1.0f }; 
		transferData[6] = { 0.5f,  0.5f,  0.5f, 1.0f, 0.0f }; 
		transferData[7] = { -0.5f,  0.5f,  0.5f, 0.0f, 0.0f };

		auto indexData = reinterpret_cast<Uint16*>(&transferData[8]);

		Uint16 indices[] = {
			// Face arrière (-Z)
			0, 1, 2,  0, 2, 3,
			// Face avant (+Z)
			4, 6, 5,  4, 7, 6,
			// Face gauche (-X)
			4, 0, 3,  4, 3, 7,
			// Face droite (+X)
			1, 5, 6,  1, 6, 2,
			// Face bas (-Y)
			4, 5, 1,  4, 1, 0,
			// Face haut (+Y)
			3, 2, 6,  3, 6, 7
		};
		memcpy(indexData, indices, sizeof(indices));

		renderer.UnmapTransferBuffer(transferBuffer);

		// Setup texture transfer buffer
		Uint32 bufferSize = imageData->w * imageData->h * 8;
		SDL_GPUTransferBufferCreateInfo textureTransferBufferCreateInfo{
		.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
		.size = bufferSize
		};
		SDL_GPUTransferBuffer* textureTransferBuffer =
			renderer.CreateTransferBuffer(textureTransferBufferCreateInfo);
		auto textureTransferData = static_cast<PositionTextureVertex*>(renderer.MapTransferBuffer(textureTransferBuffer, false));
		std::memcpy(textureTransferData, imageData->pixels, bufferSize);
		renderer.UnmapTransferBuffer(textureTransferBuffer);
		renderer.BeginUploadToBuffer();

		// Upload the transfer data to the vertex and index buffer
		SDL_GPUTransferBufferLocation transferVertexBufferLocation{
		.transfer_buffer = transferBuffer,
		.offset = 0
		};
		SDL_GPUBufferRegion vertexBufferRegion{
		.buffer = vertexBuffer,
		.offset = 0,
		.size = sizeof(PositionTextureVertex) * 8
		};
		SDL_GPUTransferBufferLocation transferIndexBufferLocation{
		.transfer_buffer = transferBuffer,
		.offset = sizeof(PositionTextureVertex) * 8
		};
		SDL_GPUBufferRegion indexBufferRegion{
		.buffer = indexBuffer,
		.offset = 0,
		.size = sizeof(Uint16) * 36
		};
		SDL_GPUTextureTransferInfo textureBufferLocation{
		.transfer_buffer = textureTransferBuffer,
		.offset = 0
		};
		SDL_GPUTextureRegion textureBufferRegion{
		.texture = texture,
		.w = static_cast<Uint32>(imageData->w),
		.h = static_cast<Uint32>(imageData->h),
		.d = 1
		};
		renderer.UploadToBuffer(transferVertexBufferLocation, vertexBufferRegion, false);
		renderer.UploadToBuffer(transferIndexBufferLocation, indexBufferRegion, false);
		renderer.UploadToTexture(textureBufferLocation, textureBufferRegion, false);
		renderer.EndUploadToBuffer(transferBuffer);
		renderer.ReleaseTransferBuffer(textureTransferBuffer);
		renderer.ReleaseSurface(imageData);
	}
	void Cube::Draw(Renderer::Renderer& renderer)
	{
		renderer.Begin();

		renderer.BindGraphicsPipeline(pipeline);
		SDL_GPUBufferBinding vertexBindings{ .buffer = vertexBuffer, .offset = 0 };
		renderer.BindVertexBuffers(0, vertexBindings, 1);
		SDL_GPUBufferBinding indexBindings{ .buffer = indexBuffer, .offset = 0 };
		renderer.BindIndexBuffer(indexBindings, SDL_GPU_INDEXELEMENTSIZE_16BIT);
		SDL_GPUTextureSamplerBinding textureSamplerBinding{ .texture = texture, .sampler = sampler };
		renderer.BindFragmentSamplers(0, textureSamplerBinding, 1);

		Maths::Mat4 model = Maths::Mat4::CreateRotationMatrix(0.0, 1.0, 0.0, 30 * (3.1415 / 180)) * Maths::Mat4::CreateTranslation(0.0f, 0.0f, -3.0f);
		Maths::Mat4 view = Maths::Mat4::Identity;
		Maths::Mat4 projection = Maths::Mat4::CreatePerspectiveFieldOfView(90.0f * (3.1415 / 180), 640.0f / 480.0f, 0.1f, 1000.0f);

		Maths::Mat4 mvp = model * view * projection;
		renderer.PushVertexUniformData(0, &mvp, sizeof(mvp));

		FragMultiplyUniform fragMultiplyUniform0{ 1.0f, 1.0f, 1.0f, 1.0f };
		renderer.PushFragmentUniformData(0, &fragMultiplyUniform0, sizeof(FragMultiplyUniform));
		renderer.DrawIndexedPrimitives(36, 1, 0, 0, 0);
		renderer.End();
	}
	void Cube::Unload(Renderer::Renderer& renderer)
	{
		renderer.ReleaseSampler(sampler);
		renderer.ReleaseBuffer(vertexBuffer);
		renderer.ReleaseBuffer(indexBuffer);
		renderer.ReleaseTexture(texture);
		renderer.ReleaseGraphicsPipeline(pipeline);
	}
}