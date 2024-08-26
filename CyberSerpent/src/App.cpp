#include <iostream>
#include <chrono>
#include <thread>

#include "core/engine.h"

int main()
{
	CS::Engine& engine{ CS::Engine::Get() };
	engine.Run();

	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}