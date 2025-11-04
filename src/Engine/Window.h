#ifndef WINDOW_H
#define WINDOW_H
#include <SDL3/SDL_video.h>

namespace Engine
{
	class Window
	{
	public:
		SDL_Window* sdlWindow{ nullptr };
		void Init();
		void Close() const;
		int width{ 640 };
		int height{ 480 };
	};
}
#endif