#pragma once

// forward decls
namespace CS
{
	class Shell;
}

// forward decls
class APILoader;

namespace CS
{
	namespace CORE
	{
		class Engine
		{
		public:
			void Run();

		private:
			Engine();
			~Engine();

		public:
			Engine(Engine&) = delete;

		public:
			static Engine& Get();

		private:
			APILoader& m_APILoader;
			CS::Shell* m_Shell;
		};
	}
}