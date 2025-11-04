#ifndef TIME_H
#define TIME_H

namespace Engine
{
	class Time 
	{
	public:
		float ComputeDeltaTime();
		void DelayTime();
	private:
		const static int FPS = 60;
		const static int frameDelay = 1000 / FPS;
		unsigned int frameStart{ 0 };
		unsigned int lastFrame{ 0 };
		unsigned int frameTime{ 0 };
	};
}
#endif