#include "core/Engine.h"

int main()
{
	CS::CORE::Engine& engine{ CS::CORE::Engine::Get() };
	engine.Run();
}