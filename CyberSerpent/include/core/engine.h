#pragma once

#include <iostream>
#include "utils/root_check.h"
#include "Shell.h"

namespace CS
{
	namespace CORE
	{
		class Engine
		{
		public:
			Engine() = default;
			Engine(Engine&) = delete;

		public:
			void Run() const
			{
				if (CS::UTILS::IsRoot())
					std::cout << "ROOT!\n";
				else
					std::cout << ":(\n";

				std::cin.get();
				CS::Shell::Get().clear();
			}

		public:
			static Engine& Get()
			{
				static Engine s_Instance{};
				return s_Instance;
			}
		};
	}
}