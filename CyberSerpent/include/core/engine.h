#pragma once

#include "utils/root_check.h"

namespace CS
{
	class Engine
	{
	public:
		Engine() = default;
		Engine(Engine&) = delete;

	public:
		void Run() const
		{
			if (CS::IsRoot())
				std::cout << "ROOT!\n";
			else
				std::cout << ":(\n";
		}

	public:
		static Engine& Get()
		{
			static Engine s_Instance{};
			return s_Instance;
		}
	};
}