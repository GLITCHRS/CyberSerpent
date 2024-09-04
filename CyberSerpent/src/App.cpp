#include <iostream>
#include <chrono>
#include <thread>

#include "core/engine.h"

int main()
{
	CS::CORE::Engine& engine{ CS::CORE::Engine::Get() };
	engine.Run();
}