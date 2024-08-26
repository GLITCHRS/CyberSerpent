#include <iostream>

#include "Engine.h"

int main()
{
	CS::Engine& engine{ CS::Engine::Get() };
	engine.Run();

	Sleep(2000);
}