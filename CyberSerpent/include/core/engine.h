#pragma once

// forward decls
namespace CS
{
	class Shell;
}

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

		public:
			Engine(Engine&) = delete;

		public:
			static Engine& Get();

		private:
			CS::Shell* m_Shell;
		};
	}
}