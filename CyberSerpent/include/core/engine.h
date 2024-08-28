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

				std::string command;
				while (true)
				{
					std::cout << CS::Shell::s_ShellPrefix;
					std::cin >> command;

					if (m_Shell.m_Commands.contains(command))
					{
						try
						{
							(m_Shell.*m_Shell.m_Commands[command])();
						}
						catch (exception_exit&)
						{
							break;
						}
					}
				}
			}
			
		public:
			static Engine& Get()
			{
				static Engine s_Instance{};
				return s_Instance;
			}

		private:
			CS::Shell& m_Shell{ CS::Shell::Get() };
		};
	}
}