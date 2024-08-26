#pragma once

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
			std::cout << "Hello World\n";
		}

	public:
		static Engine& Get()
		{
			static Engine s_Instance{};
			return s_Instance;
		}
	};
}